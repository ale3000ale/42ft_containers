
#ifndef SET_HPP
# define SET_HPP

# include <memory> // for std::allocator
# include "utils.hpp"
# include "BaseTree.hpp"

//#include <set>

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
		typedef typename _base::iterator				 iterator;
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
		pair<iterator,bool> insert(const value_type& v);
		iterator insert(const_iterator position, const value_type& v);
		template <class InputIterator>
			void insert(InputIterator first, InputIterator last);

		iterator  erase(const_iterator position);
		size_type erase(const key_type& k);
		iterator  erase(const_iterator first, const_iterator last);
		void clear() noexcept;

		void swap(set& s);

		// observers:
		allocator_type get_allocator() const;
		key_compare    key_comp()      const;
		value_compare  value_comp()    const;

		// set operations:
		iterator find(const key_type& k);
		const_iterator find(const key_type& k) const;
		template<typename K>
			iterator find(const K& x);

		size_type      count(const key_type& k) const;
		iterator lower_bound(const key_type& k);
		const_iterator lower_bound(const key_type& k) const;

		iterator upper_bound(const key_type& k);
		const_iterator upper_bound(const key_type& k) const;
		pair<iterator,iterator>             equal_range(const key_type& k);
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const;
	private:
		_base	_tree;
	};

	template <class Key, class Compare, class Allocator>
	bool operator==(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y);

	template <class Key, class Compare, class Allocator>
	bool operator< (const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y);

	template <class Key, class Compare, class Allocator>
	bool operator!=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y);

	template <class Key, class Compare, class Allocator>
	bool operator> (const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y);

	template <class Key, class Compare, class Allocator>
	bool operator>=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y);

	template <class Key, class Compare, class Allocator>
	bool operator<=(const set<Key, Compare, Allocator>& x, const set<Key, Compare, Allocator>& y);

	// specialized algorithms:
	template <class Key, class Compare, class Allocator>
	void swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y);
	
} // namespace ft


#endif