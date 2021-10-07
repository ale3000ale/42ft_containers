


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

			node_pointer parent() const
				{ return (parent); }
			void set_parent(node_pointer p)
				{ parent = p; }
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
			node_pointer							_begin_node;
			node_pointer							_end_node;
			pair<node_allocator, value_allocator>	_allocators;
			size_type								_size;
			value_compare							_comp;

		public:
			tree(value_allocator& alloc)
				: _begin_node(nullptr), _end_node(nullptr), _allocators(make_pair(node_allocator(), alloc)), _size(0), _comp(value_compare()) {};
			tree(value_compare& comp, value_allocator& alloc = value_allocator())
				: _begin_node(nullptr), _end_node(nullptr), _allocators(make_pair(node_allocator(), alloc)), _size(0), _comp(comp) {};
			// copy constructor just copies tree conf but not the elements
			tree(tree const & other, value_allocator& alloc = value_allocator(other._value_allocator()))
				: _begin_node(nullptr), _end_node(nullptr), _allocators(make_pair(node_allocator(node_allocator()), value_allocator(alloc))), _size(0), _comp(value_compare()) {};
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
				{ return (iterator(_begin_node)); };
			const_iterator begin() const
				{ return (const_iterator(_begin_node)); }
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
				/* TODO */
			}
			iterator insert(const_iterator pos, const value_type& v)
			{
				/* TODO */
			}
			
			iterator erase(const_iterator pos)
			{
				/* TODO */
			}
			iterator erase(const_iterator first, const_iterator last)
			{
				while (first != last)
					first = erase(first);
				return (iterator(last));
			}
			void erase(const key_type& k)
			{
				iterator i = find(k);
				if (i == end())
					return (0);
				erase(i);
				return (1);
			}

			void clear()
			{
				// add destroy method
				_size = 0;
				_begin_node = nullptr;
				_end_node = nullptr; // maybe not necessary
			}

			void swap(tree& other)
			{
				ft::swap(this->_begin_node, other._begin_node);
				ft::swap(this->_end_node, other._end_node);
				this->_allocators.swap(other._allocators);
				ft::swap(this->_size, other._size);
				ft::swap(this->_comp, other._comp);
			}
			/* NEEDED FUNCTIONS 
				- Find
				- Count
				- lower_bound/upper_bound
				- Equal_range */

	};
};