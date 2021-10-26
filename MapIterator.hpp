
#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "iterator"
# include "Node.hpp" 

namespace ft
{
	template <class T, class DiffType> /* T = type on which the node is templated (tree_node<t>) 
											DiffType = Allocator::difference_type */
	class tree_iterator
	{
		typedef binary_node<T>	_node_type;
		_node_type 				*_ptr;

	public:
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef DiffType					difference_type;
		typedef value_type&					reference;
		typedef const value_type&		    const_reference;
		typedef value_type*					pointer;
		//typedef const value_type*			const_pointer;

		tree_iterator() : _ptr(nullptr) {};
		/* tree_iterator(tree_iterator<value_type, difference_type> const & other) : _ptr(other._ptr) {}; */
		~tree_iterator() {};

		/*const_reference operator*() const
			{ return (_ptr->value()); };
		const pointer operator->() const
			{ return (&(_ptr->_value)); };*/
		reference operator*() const
			{ return (_ptr->value()); };
		pointer operator->() const
			{ return (&(_ptr->value())); };

		tree_iterator& operator++()
		{
			_ptr = tree_next_node(_ptr);
			return (*this);
		};
		tree_iterator operator++(int)
		{
			tree_iterator tmp(*this);
			++(*this);
			return (tmp);
		};

		tree_iterator& operator--()
		{
			_ptr = tree_prev_node(_ptr);
			return (*this);
		};
		tree_iterator operator--(int)
		{
			tree_iterator tmp(*this);
			--(*this);
			return (tmp);
		};

		

		_node_type	*base() const
			{ return(_ptr); };

	private:
		explicit tree_iterator(_node_type *p) : _ptr(p) {};

		template <class, class, class> friend class base_tree;
		template <class, class> friend class tree_const_iterator;
		template <class, class, class, class> friend class map;
		//template <class, class, class> friend class set;
	};

	template <class T, class DiffType>
	bool operator==(const tree_iterator<T,DiffType>& x, const tree_iterator<T,DiffType>& y)
		{ return (x.base() == y.base()); };

	template <class T, class DiffType>	
	bool operator!=(const tree_iterator<T,DiffType>& x, const tree_iterator<T,DiffType>& y)
		{ return (!(x == y)); };

	template <class T, class DiffType> /* T = type on which the node is templated (tree_node<t>) 
										DiffType = Allocator::difference_type */
	class tree_const_iterator
	{
		typedef binary_node<T>	_node_type; //tree_node to be implemented
		_node_type 		*_ptr;

	public:
		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef DiffType							difference_type;
		typedef const value_type&							reference;
		typedef const value_type*					pointer; // dont know if correct to put keyword const there
	private:
		typedef tree_iterator<value_type, difference_type> _non_const_iterator;
	public:
		tree_const_iterator() : _ptr(nullptr) {};
		tree_const_iterator(const _non_const_iterator i) : _ptr(i._ptr) {};
		~tree_const_iterator() {};

		reference operator*() const
			{ return (_ptr->value()); };
		pointer operator->() const
			{ return (&(_ptr->value())); };

		tree_const_iterator& operator++()
		{
			_ptr = tree_next_node(_ptr);
			return (*this);
		};
		tree_const_iterator operator++(int)
		{
			tree_const_iterator tmp(*this);
			++(*this);
			return (tmp);
		};

		tree_const_iterator& operator--()
		{
			_ptr = tree_prev_node(_ptr);
			return (*this);
		};
		tree_const_iterator operator--(int)
		{
			tree_const_iterator tmp(*this);
			--(*this);
			return (tmp);
		};
		const _node_type	*base() const
			{ return(_ptr); };

	private:
		explicit tree_const_iterator(_node_type *p) : _ptr(p) {};

		template <class, class, class> friend class tree;
		template <class, class, class> friend class base_tree;
		template <class, class, class, class> friend class map;
		//template <class, class, class> friend class set;
	};
	template <class T, class DiffType>
	bool operator==(const tree_const_iterator<T,DiffType>& x, const tree_const_iterator<T,DiffType>& y)
		{ return (x.base() == y.base()); };

	template <class T, class DiffType>
	bool operator!=(const tree_const_iterator<T,DiffType>& x, const tree_const_iterator<T,DiffType>& y)
		{ return (!(x == y)); };

	template <class T, class DiffType>
	bool operator==(const tree_const_iterator<T,DiffType>& x, const tree_iterator<T,DiffType>& y)
		{ return (x.base() == y.base()); };

	template <class T, class DiffType>
	bool operator!=(const tree_const_iterator<T,DiffType>& x, const tree_iterator<T,DiffType>& y)
		{ return (!(x == y)); };
	
	template <class T, class DiffType>
	bool operator==(const tree_iterator<T,DiffType>& x, const tree_const_iterator<T,DiffType>& y)
		{ return (x.base() == y.base()); };

	template <class T, class DiffType>
	bool operator!=(const tree_iterator<T,DiffType>& x, const tree_const_iterator<T,DiffType>& y)
		{ return (!(x == y)); };
};

#endif