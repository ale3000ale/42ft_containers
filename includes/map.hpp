/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:18:54 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/10/26 17:17:55 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory> // for std::allocator
# include <exception> // for std::out_of_range
# include "utils.hpp"
# include "pair.hpp"
# include "BaseTree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = less<Key>,
		class Allocator = std::allocator< pair <const Key, T> > >
	class map
	{
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef pair<const key_type, mapped_type>					value_type;
		typedef Compare												key_compare;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;
	
		class value_compare
			: public std::binary_function<value_type, value_type, bool>
		{
				friend class map;
				key_compare comp;
			public:
				value_compare(key_compare c) : comp(c) {};
				value_compare() : comp(key_compare()) {};
				bool operator()(const value_type& x, const value_type& y) const
					{ return(comp(x.first, y.first)); };
		};
	private:
		typedef base_tree<value_type, value_compare, allocator_type>	_base;
		typedef typename std::allocator<_base> 						_tree_allocator;
	public:
		typedef typename _base::iterator							iterator;
		typedef typename _base::const_iterator						const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		// construct/copy/destroy:
		explicit map(const key_compare& comp = key_compare()) : _tree(key_compare(comp)) {};

		map(const key_compare& comp, const allocator_type& a) : _tree(key_compare(comp), allocator_type(a)) {} ;
		
		template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare())
				: _tree(key_compare(comp))
			{ insert(first, last); };
		
		template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp, const allocator_type& a)
				: _tree(key_compare(comp), allocator_type(a))
			{ insert(first, last); };
		
		map(const map& m, const allocator_type& a = allocator_type()) : _tree(m._tree, allocator_type(a)) {};
		
		explicit map(const allocator_type& a) : _tree(allocator_type(a)) {};
		
		~map() {};

		map& operator=(const map& m)
		{
			if (this != &m)
            	_tree = m._tree;
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

		// element access:
		mapped_type& operator[](const key_type& k)
		{
			iterator node = find(k);
			if (node == end())
				node = _tree.insert(_new_pair(k)).first;
			return ((*node).second);
		};

		mapped_type& at(const key_type& k)
		{
			iterator node = find(_new_pair(k));
			if (node == end())
				throw(std::out_of_range("map::at:  key not found"));
			return ((*node).second);
		}
		const mapped_type& at(const key_type& k) const
		{
			iterator node = find(_new_pair(k));
			if (node == end())
				throw(std::out_of_range("map::at:  key not found"));
			return ((*node).second);
		};

		pair<iterator, bool>	insert(const value_type& v)
			{ return (_tree.insert(v)); };
		
		iterator				insert(const_iterator position, const value_type& v)
			{
				if (position != cend())
					++position;
				return (_tree.insert(v).first);
			};
		
		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			for (const_iterator e = cend(); first != last; ++first)
				insert(*first);
		};

		iterator  erase(const_iterator position)
			{ return (_tree.erase(position)); };
		size_type erase(const key_type& k)
			{ return (_tree.erase(_new_pair(k))); };
		iterator  erase(const_iterator first, const_iterator last)
			{ return (_tree.erase(first, last)); };
		void clear()
			{ _tree.clear_all(); };

		// observers:
		allocator_type get_allocator() const
			{ return (allocator_type(_tree._node_allocator())); };
		key_compare    key_comp()      const
			{ return (key_compare());};
		value_compare  value_comp()    const
			{ return (value_compare(key_comp())); };

		// map operations:
		iterator		find(const key_type& k)
			{ return (_tree.find(_new_pair(k))); };
		const_iterator	find(const key_type& k) const
			{ return (_tree.find(_new_pair(k))); };

		size_type      count(const key_type& k) const
			{ return (_tree.count(_new_pair(k))); };

		iterator		lower_bound(const key_type& k)
			{ return (_tree.lower_bound(_new_pair(k))); };
		const_iterator	lower_bound(const key_type& k) const
			{ return (_tree.lower_bound(_new_pair(k))); };

		iterator		upper_bound(const key_type& k)
			{ return (_tree.upper_bound(_new_pair(k))); };
		const_iterator	upper_bound(const key_type& k) const
			{ return (_tree.upper_bound(_new_pair(k))); };

		pair<iterator,iterator>             equal_range(const key_type& k)
			{ return (_tree.equal_range(_new_pair(k))); };
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const
			{ return (_tree.equal_range(_new_pair(k))); };

		void swap(map& m)
			{ _tree.swap(m._tree); };

	private:

		_base	_tree;
		value_type _new_pair(const key_type& k) const
			{ return(ft::make_pair(k, mapped_type())); };

	}; // class map

	template <class Key, class T, class Compare, class Allocator>
	bool operator==(const map<Key, T, Compare, Allocator>& x,
			        const map<Key, T, Compare, Allocator>& y)
	{
		return ((x.size() == y.size()) && (equal(x.begin(), x.end(), y.begin())));
	};
	template <class Key, class T, class Compare, class Allocator>
	bool operator< (const map<Key, T, Compare, Allocator>& x,
			        const map<Key, T, Compare, Allocator>& y)
	{
		return (lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	};
	template <class Key, class T, class Compare, class Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator>& x,
			        const map<Key, T, Compare, Allocator>& y)
		{ return (!(x == y)); };

	template <class Key, class T, class Compare, class Allocator>
	bool operator> (const map<Key, T, Compare, Allocator>& x,
			        const map<Key, T, Compare, Allocator>& y)
		{ return (y < x); };

	template <class Key, class T, class Compare, class Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator>& x,
			        const map<Key, T, Compare, Allocator>& y)
		{  return (!(x < y)); };

	template <class Key, class T, class Compare, class Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator>& x,
			        const map<Key, T, Compare, Allocator>& y)
		{ return (!(y < x)); };

	// specialized algorithms:
	template <class Key, class T, class Compare, class Allocator>
	void
	swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
		{ x.swap(y); };

}; // namespace ft

#endif