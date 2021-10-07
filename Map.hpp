/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:18:54 by alexmarcell       #+#    #+#             */
/*   Updated: 2021/09/29 12:07:09 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H__
# define MAP_H__

# include <memory> // for std::allocator
# include "utils.hpp"
# include "pair.hpp"
# include "iterator.hpp"
# include "MapIterator.hpp"

# include <map>

std::map<int, int> t;

namespace ft
{
	template <class Key, class T, class Compare = less<Key>,
			class Allocator = std::allocator< pair <const Key, T> > >
	class map
	{
	public:
		typedef Key                                      			key_type;
		typedef T                                        			mapped_type;
		typedef pair<const key_type, mapped_type>        			value_type;
		typedef Compare                                  			key_compare;
		typedef Allocator                                			allocator_type;
		typedef typename allocator_type::reference       			reference;
		typedef typename allocator_type::const_reference 			const_reference;
		typedef typename allocator_type::pointer         			pointer;
		typedef typename allocator_type::const_pointer   			const_pointer;
		typedef typename allocator_type::size_type       			size_type;
		typedef typename allocator_type::difference_type			difference_type;

		typedef tree_iterator<value_type, difference_type>			iterator;
		typedef tree_const_iterator<value_type, difference_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>          			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    			const_reverse_iterator;

		class value_compare
			: public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;

			value_compare(key_compare c) : comp(c) {};
		public:
			bool operator()(const value_type& x, const value_type& y) const
				{ return(comp(x.first, y.first)); };
		};

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
		map(const map& m) : _tree(m._tree)
			{ insert(m.begin(), m.end()); /* why do i have to insert em if i already copy-created mine? */ };
		explicit map(const allocator_type& a) : _tree(allocator_type(a)) {};
		map(const map& m, const allocator_type& a) : _tree(m._tree, allocator_type(a))
			{ insert(m.begin(), m.end()); /* why do i have to insert em if i already copy-created mine? */ };
		~map();

		map& operator=(const map& m)
		{
			if (this != &m)
			{
                _tree.clear();
                insert(m.begin(), m.end());
            }
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

		const_iterator         cbegin() const { return (begin()); };
		const_iterator         cend() const { return (end()); };
		const_reverse_iterator crbegin() const { return (rbegin()); };
		const_reverse_iterator crend() const { return (rend()); };

		// capacity:
		bool      empty()    const { return (_tree.size() == 0); };
		size_type size()     const { return (_tree.size()); };
		size_type max_size() const { return (_tree.max_size()); };

		// element access:
		mapped_type& operator[](const key_type& k)
		{
			/* PSEUDO - CODE */
			/*
			child = _tree.find_equal(pointer_to_begin, k);
			if (child == nullptr)
			{
				new_node = construct_node_with_key(k);
				_tree.insert(new_node);;
			}
			return (child or new_node value);
			*/
		};

		mapped_type& at(const key_type& k);
		{
			/* PSEUDO - CODE */
			/*
			node = _tree.find_equal(pointer_to_begin, k);
			if (node == nullptr)
				__throw_out_of_range("map::at:  key not found");
			return node value;
			**/
		}
		const mapped_type& at(const key_type& k) const
		{
			// same as non-const at
		};

		// modifiers:
		/* all these functs depend on tree implementation */
		pair<iterator, bool>	insert(const value_type& v)
			{ return (_tree.insert(v)); };
		iterator				insert(const_iterator position, const value_type& v)
			{ return (_tree.insert(position, v)); };
		template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				for (const_iterator e = cend(); first != last; ++first)
                	insert(e, *first);
			};

		iterator  erase(const_iterator position);
		size_type erase(const key_type& k);
		iterator  erase(const_iterator first, const_iterator last);
		void clear();

		// observers:
		allocator_type get_allocator() const
			{ return (allocator_type(_tree._node_allocator())); }; // needs check
		key_compare    key_comp()      const
			{ return (key_compare(_tree._value_compare()))};
		value_compare  value_comp()    const
			{ return (value_compare(key_comp())); };

		// map operations:
		iterator		find(const key_type& k);
		const_iterator	find(const key_type& k) const;

		size_type      count(const key_type& k) const;

		iterator		lower_bound(const key_type& k);
		const_iterator	lower_bound(const key_type& k) const;

		iterator		upper_bound(const key_type& k);
		const_iterator	upper_bound(const key_type& k) const;

		pair<iterator,iterator>             equal_range(const key_type& k);
		pair<const_iterator,const_iterator> equal_range(const key_type& k) const;

		void swap(map& m)
			{ _tree.swap(m._tree); };

	private:
		tree<value_type, key_compare, allocator_type>	_tree;
	};

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

};

#endif