
#ifndef UTILS_HPP
# define UTILS_HPP

# include <algorithm>
# include "iterator.hpp"

namespace ft 
{
	template <class T>
	void swap(T &a, T &b)
	{
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}

	template <bool, class _Tp = void>
	struct enable_if {};
	template <class _Tp>
	struct enable_if<true, _Tp> 
	{
		typedef _Tp type;
	};

	template <class T>
	struct less
	{
		bool operator()(const T& x, const T& y) const
		{return x < y;}
	};

	template <class T>
	struct equal_to
	{
		bool operator()(const T& x, const T& y) const
			{return x == y;}
	};

	template <class InputIterator>
	bool lexicographical_compare(InputIterator first1, InputIterator last1,
							InputIterator first2, InputIterator last2)
	{
		return (lexicographical_compare(first1, last1, first2, last2,
											less<typename iterator_traits<InputIterator>::value_type>()));
	}
	
	template <class Compare, class InputIterator>
	bool lexicographical_compare(InputIterator first1, InputIterator last1,
							InputIterator first2, InputIterator last2, Compare comp)
	{
		for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return (false);
	}

	template <class InputIterator>
	bool equal(InputIterator first1, InputIterator last1, InputIterator first2)
	{
		typedef typename iterator_traits<InputIterator>::value_type v;
		return equal(first1, last1, first2, equal_to<v>());
	}

	template <class InputIterator, class BinaryPredicate>
	bool equal(InputIterator first1, InputIterator last1, InputIterator first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!pred(*first1, *first2))
				return (false);
		return (true);
	}
};

#endif