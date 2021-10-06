


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
			typedef tree_node<node_value_type>*	node_pointer;

			node_value_type	value;
			node_pointer	right;
			node_pointer	left;
			node_pointer	parent;
			bool			is_black;

			node_pointer parent() const
				{ return (parent); }
			void set_parent(node_pointer p)
				{ parent = p; }

			tree_node(tree_node const & other)
				{ *this = other; };
  			tree_node& operator=(tree_node const & other)
			{
				this->value = other.value;
				this->right = other.right;
				this->left = other.left;
				this->parent = other.parent;
				this->is_black = other.is_black;
				return (*this);
			};
	};
};