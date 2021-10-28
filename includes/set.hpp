
#ifndef SET_HPP
# define SET_HPP

# include <memory> // for std::allocator
# include "utils.hpp"
# include "BaseTree.hpp"

namespace ft
{
	template <class Key, class Compare = less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
	public:
		// types:
		typedef Key                                      key_type;
		typedef key_type                                 value_type;
		typedef Compare                                  key_compare;
		typedef key_compare                              value_compare;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
	private:
		typedef base_tree<value_type, key_compare, allocator_type>	_base;
	public:
		typedef typename _base::const_iterator		 	 iterator;
		typedef typename _base::const_iterator		     const_iterator;
		typedef ft::reverse_iterator<iterator>		     reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;

		// construct/copy/destroy:
		explicit set(const value_compare& comp = value_compare()) : _tree(value_compare(comp)) {};
		set(const value_compare& comp, const allocator_type& a) : _tree(value_compare(comp), allocator_type(a)) {};
		template <class InputIterator>
			set(InputIterator first, InputIterator last, const value_compare& comp = value_compare())
				: _tree(value_compare(comp))
			{ insert(first, last); };
		template <class InputIterator>
			set(InputIterator first, InputIterator last, const value_compare& comp, const allocator_type& a)
				: _tree(value_compare(comp), allocator_type(a))
			{ insert(first, last); };
		set(const set& s, const allocator_type& a = allocator_type()) : _tree(s._tree, allocator_type(a)) {};
		explicit set(const allocator_type& a) : _tree(allocator_type(a)) {};
		~set() {};

		set& operator=(const set& s)
		{
			if (this != &s)
            	_tree = s._tree;
            return (*this);
		};

		// iterators:
		iterator begin() { return (_tree.begin()); };
		const_iterator begin() const { return (_tree.begin()); };
		iterator end() { return (_tree.end()); };
		const_iterator end() const { return (_tree.end()); };

		reverse_iterator rbegin() { return (reverse_iterator(end())); };
		const_reverse_iterator rbegin() const
			{ return (const_reverse_iterator(end())); };
		reverse_iterator rend() { return (reverse_iterator(begin())); };
		const_reverse_iterator rend() const
			{ return (const_reverse_iterator(begin())); };

		const_iterator			cbegin() const { return (begin()); };
		const_iterator			cend() const { return (end()); };
		const_reverse_iterator	crbegin() const { return (rbegin()); };
		const_reverse_iterator	crend() const { return (rend()); };

		// capacity:
		bool      empty()    const { return (_tree.size() == 0); };
		size_type size()     const { return (_tree.size()); };
		size_type max_size() const { return (_tree.max_size()); };

		// modifiers:
		pair<iterator,bool> insert(const value_type& v)
			{ return (_tree.insert(v)); };
		iterator insert(const_iterator position, const value_type& v)
			{ 
				if (position != cend())
					++position;
				return (_tree.insert(v)).first; };
		template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (const_iterator e = cend(); first != last; ++first) // needs check
                	insert(e, *first);
			};
		iterator  erase(const_iterator position)
			{ return (_tree.erase(position)); };
		size_type erase(const key_type& k)
			{ return (_tree.erase(k)); };
		iterator  erase(const_iterator first, const_iterator last)
			{ return (_tree.erase(first, last)); };
		void clear()
			{ _tree.clear_all(); };

		void swap(set& s)
			{ _tree.swap(s._tree); };

		// observers:
		allocator_type get_allocator() const
			{ return (allocator_type(_tree._node_allocator())); };
		key_compare    key_comp()      const
			{ return (key_compare(_tree._value_compare()));};
		value_compare  value_comp()    const
			{ return (key_compare(_tree._value_compare()));};

		// set operations:
		iterator		find(const key_type& k)
			{ return (_tree.find(k)); };
		const_iterator	find(const key_type& k) const
			{ return (_tree.find(k)); };

		size_type      count(const key_type& k) const
			{ return (_tree.count(k)); };

		iterator		lower_bound(const key_type& k)
			{ return (_tree.lower_bound(k)); };
		const_iterator	lower_bound(const key_type& k) const
			{ return (_tree.lower_bound(k)); };

		iterator		upper_bound(const key_type& k)
			{ return (_tree.upper_bound(k)); };
		const_iterator	upper_bound(const key_type& k) const
			{ return (_tree.upper_bound(k)); };
		
		pair<iterator,iterator>             equal_range(const key_type& k)
			{ return (_tree.equal_range(k)); };
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{ return (_tree.equal_range(k)); };
	private:
		_base	_tree;
	}; // class set

	template <class Key, class Compare, class Allocator>
	bool operator==(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y)
	{
		return ((x.size() == y.size()) && (equal(x.begin(), x.end(), y.begin())));
	};

	template <class Key, class Compare, class Allocator>
	bool operator< (const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y)
	{
		return (lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	};

	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y)
		{ return (!(x == y)); };

	template <class Key, class Compare, class Allocator>
	bool operator> (const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y)
		{ return (y < x); };

	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y)
		{  return (!(x < y)); };

	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y)
		{ return (!(y < x)); };

	// specialized algorithms:
	template <class Key, class Compare, class Allocator>
	void swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
		{ x.swap(y); };
	
} // namespace ft


#endif