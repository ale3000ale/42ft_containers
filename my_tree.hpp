


namespace ft
{
	template <class NodePtr>
	bool tree_is_left_child(NodePtr x)
	{
		return (x == x->parent->left);
	}

	// Returns:  pointer to the left-most node under x.
	template <class NodePtr>
	NodePtr tree_min(NodePtr x)
	{
		while (x->left != nullptr)
			x = x->left;
		return (x);
	}

	// Returns:  pointer to the right-most node under x.
	template <class NodePtr> 
	NodePtr tree_max(NodePtr x)
	{
		while (x->right != nullptr)
			x = x->right;
		return (x);
	}

	template <class NodePtr>
	NodePtr tree_next_node(NodePtr x)
	{
		if (x->right != nullptr)
			return (tree_min(x->right));
		while (!tree_is_left_child(x))
			x = x->parent();
		return (x->parent());
	}

	template <class NodePtr>
	NodePtr tree_prev_node(NodePtr x)
	{
		if (x->_left != nullptr)
			return (tree_max(x->left));
		while (tree_is_left_child(x))
			x = x->parent();
		return (x->parent());
	}

	/* dont know if this class will be useful */
	template <class Allocator>
	class tree_node_destructor
	{
		typedef Allocator										allocator_type;

		public:
			typedef typename allocator_type::pointer			pointer;
		private:
			allocator_type& _alloc;

			tree_node_destructor& operator=(const tree_node_destructor& other)
			{
				this->_alloc = other._alloc;
				this->_value_constructed = other._value_constructed;
			};
		public:
			bool _value_constructed;

			explicit tree_node_destructor(allocator_type& a, bool val = false)
				: _alloc(a), _value_constructed(val)
			{}

			void operator()(pointer p)
			{
				if (_value_constructed)
					_alloc.destroy(p);
				if (p)
					_alloc.deallocate(p, 1);
			}
		};

	/*
		node
	*/
	/*
		TODO gestire end_node, o aggiungo una variabile al nodo o creo una classe apposita, oppure nessuno dei due in realtá
		si potrebbe implementare come fa la libreria standard, end_node->left punta a root.
	*/
	template <class T>
	class tree_node
	{
		public:
			typedef T 							node_value_type;
			typedef node_value_type*			value_pointer;
 			typedef tree_node<node_value_type>*	node_pointer;

			value_pointer	value;
			node_pointer	right;
			node_pointer	left;
			node_pointer	parent;
			bool			is_black;

			node_value_type value() const
				{ return (*value); };
			node_pointer parent() const
				{ return (parent); };
			void set_parent(node_pointer p)
				{ parent = p; };
			tree_node() : value(nullptr), right(nullptr), left(nullptr), parent(nullptr), is_black(true) {};
			tree_node(tree_node const & other)
				{ *this = other; };
  			tree_node& operator=(tree_node const & other)
			{
				this->value = other.value; // sistemare, questa non fa deep copy.
				this->right = other.right;
				this->left = other.left;
				this->parent = other.parent;
				this->is_black = other.is_black;
				return (*this);
			};
	};

	/*
		tree
	*/
	template <class T, class Compare, class Allocator>
	class tree
	{
		public:
			typedef T											value_type;
			typedef typename value_type::first_type				key_type;
			typedef tree_node<T>								node_type;
			typedef typename node_type::node_pointer			node_pointer;
			typedef std::allocator<node_type>					node_allocator;
			typedef Allocator									value_allocator;
			typedef typename node_allocator::size_type			size_type;
			typedef typename node_allocator::difference_type	difference_type;
			typedef Compare										value_compare;

			typedef tree_iterator<value_type, difference_type>			iterator;
			typedef tree_const_iterator<value_type, difference_type>	const_iterator;
			
		private:
			node_pointer							_root;
			node_pointer							_end_node; // element following the last element of the tree
			pair<node_allocator, value_allocator>	_allocators;
			size_type								_size;
			value_compare							_comp;

		public:
			tree(value_allocator& alloc)
				:_root(nullptr), _end_node(nullptr), _allocators(make_pair(node_allocator(), alloc)), _size(0), _comp(value_compare()) {};
			tree(value_compare& comp, value_allocator& alloc = value_allocator())
				:_root(nullptr), _end_node(nullptr), _allocators(make_pair(node_allocator(), alloc)), _size(0), _comp(comp) {};
			// copy constructor just copies tree conf but not the elements
			tree(tree const & other, value_allocator& alloc = value_allocator(other._value_allocator()))
				:_root(nullptr), _end_node(nullptr), _allocators(make_pair(node_allocator(node_allocator()), value_allocator(alloc))), _size(0), _comp(value_compare()) {};
			~tree() { /*TODO */ };
			tree& operator=(const tree& other)
			{
				if (this != &other)
				{
					_allocators.second = value_allocator(other._value_allocator());
					_comp = value_compare(other._comp);					
				}
				return (*this);
			}

          	iterator begin()
				{ return (iterator(_root)); };
			const_iterator begin() const
				{ return (const_iterator(_root)); }
			iterator end()
				{ return (iterator(_end_node)); };
			const_iterator end() const
				{ return (const_iterator(_end_node)); }
			
			node_allocator const &	_node_allocator() const
				{ return (_allocators.first) };
			value_allocator const & _value_allocator() const
				{ return (_allocators.second) };
			value_compare const & _value_compare() const
				{ return (_comp) };

			const size_type& size() const
				{ return (_size); };
			size_type max_size() const
				{ return (_node_allocator().max_size()) };

			pair<iterator, bool> insert(const value_type& v)
			{
				node_pointer parent;
				node_pointer child = _find_equal(parent, v.first);
				bool inserted = false;
				if (!child)
				{
					node_pointer new_node = _construct_node(v);
					_insert_node_at(parent, child, new_node); // needs implementation
					child = new_node;
					inserted = true;
				}
				return (pair<iterator, bool>(iterator(child), inserted));
			};
			iterator insert(const_iterator pos, const value_type& v)
			{
				node_pointer parent;
				node_pointer child = _find_equal(pos, parent, v.first);
				bool inserted = false;
				if (!child)
				{
					node_pointer new_node = _construct_node(v);
					_insert_node_at(parent, child, new_node); // needs implementation
					child = new_node;
					inserted = true;
				}
				return (iterator(child));
			};
			
			iterator erase(const_iterator pos)
			{
				/* TODO */
			};
			iterator erase(const_iterator first, const_iterator last)
			{
				while (first != last)
					first = erase(first);
				return (iterator(last));
			};
			void erase(const key_type& k)
			{
				iterator i = find(k);
				if (i == end())
					return (0);
				erase(i);
				return (1);
			};

			void clear()
			{
				/* TODO add destroy method */
				_size = 0;
				_root = nullptr;
				_end_node = nullptr; // maybe not necessary
			};

			void swap(tree& other)
			{
				ft::swap(this->_root, other._root);
				ft::swap(this->_end_node, other._end_node);
				this->_allocators.swap(other._allocators);
				ft::swap(this->_size, other._size);
				ft::swap(this->_comp, other._comp);
			};

			iterator find(const key_type& k)
			{
				iterator i = lower_bound(k);
				if ((i != end()) && (!_comp(k, *i)))
					return (i);
				return (end());
			};
			const_iteartor find(const key_type& k) const
			{
				const_iterator i = lower_bound(k);
				if ((i != end()) && (!_comp(k, *i)))
					return (i);
				return (end());
			};
			
			size_type count(const key_type& k) const
			{
				node_pointer ptr =_root;
				while (ptr)
				{
					if (_comp(k, ptr->value())) // k < value
						ptr = ptr->left;
					else if (_comp(ptr->value(), k)) // value < k
						ptr = ptr->right;
					else // k == value
						return (1);
				}
				return (0);
			}

			iterator lower_bound(const key_type& k, node_pointer root =_root)
			{
				node_pointer result = _end_node;
				while (root)
				{
					if (!(_comp(root->value(), k))) // value >= k
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}
			const_iterator lower_bound(const key_type& k) const
				{ return (lower_bound(k)); };

			iterator upper_bound(const key_type& k, node_pointer root = _root)
			{
				node_pointer result = _end_node;
				while (root)
				{
					if ((_comp(k, root->value()))) // k < value
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}
			const_iterator upper_bound(const key_type& k) const
				{ return (upper_bound(k)); };
			
			pair<iterator,iterator> equal_range(const key_type& k)
			{ return (pair<iterator,iterator>(lower_bound(k), upper_bound(k))); };

			pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{ return (pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k))); };
		
		private:
			/*
			Find place to insert if k doesn't exist
			Set parent to parent of null leaf
			Return reference to null leaf
			If k exists, set parent to node of k and return reference to node of k
			*/
			node_pointer& _find_equal(node_pointer& parent, Key k)
			{
				node_pointer nd = _root;
				if (nd)
				{
					while (true)
					{
						if (_comp(k, nd->value())) // k < value
						{
							if (nd->left)
								nd = nd->left;
							else
							{
								parent = nd;
								return (nd->left);
							}
						}
						else if (_comp(nd->value(), k)) // value < k
						{
							if (nd->right)
								nd = nd->right;
							else
							{
								parent = nd;
								return (nd->right);
							}
						}
						else
						{
							parent = nd;
							return (nd);
						}
					}
				}
				parent = nullptr; // da gestire meglio se faccio end_node->left = root
				return (nullptr);
				/*
					parent = end_node();
					return (parent->left);
				*/
			};

			/*
			Find place to insert if k doesn't exist
			First check prior to hint.
			Next check after hint.
			Next search with _find_equal.
			*/
			node_pointer& _find_equal(const_iterator hint, node_pointer& parent, Key k)
			{
				if (hint == end() || _comp(k, *hint)) // check_before
				{
					// k < *hint
					const_iterator prior = hint;
					if (prior == begin() || _comp(*(--prior), k))
					{
						// *prev(hint) < k < *hint
						if (!hint._ptr->left)
						{
							parent = hint._ptr;
							return (parent->left);
						}
						else
						{
							parent = prior._ptr;
							return (parent->right);
						}
					}
					// k <= *prev(hint)
					return (_find_equal(parent, k));
				}
				else if (_comp(*hint, k)) // check_after
				{
					// *hint < k
					const_iterator next = ++hint;
					if (next == end() || _comp(k, *next))
					{
						// *hint < k < *next(hint)
						if (!hint._ptr->right)
						{
							parent = hint._ptr;
							return (parent->right);
						}
						else
						{
							parent = next._ptr;
							return (parent->left);
						}
					}
					// *next(hint) <= k
					return (_find_equal(parent, k));
				}
				// k == *hint
				parent = hint._ptr;
				return (hint._ptr);
			};

			node_pointer _construct_node(const value_type& v)
			{
				node_allocator& na = _node_allocator();
				value_allocator& va = _value_allocator();

				node_pointer nd = na.allocate(1);
				na.construct(nd, node_type());
				nd->value = va.allocate(1);
				va.construct(nd->value, v);
			};

			void _insert_node_at(node_pointer parent, node_pointer& child, node_pointer new_node)
			{
				new_node->left   = nullptr;
				new_node->right  = nullptr;
				new_node->parent = parent;
				// new_node->is_black is initialized in _tree_balance_after_insert
				child = new_node;
				// dont really understand next lines
				/*if (__begin_node()->__left_ != nullptr)
					__begin_node() = static_cast<__iter_pointer>(__begin_node()->__left_);*/
				//_tree_balance_after_insert(__end_node()->__left_, __child);
				_tree_balance_after_insert(_root, child);
				++_size;
			};
	};
};















