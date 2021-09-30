
#ifndef UTILS_HPP
# define UTILS_HPP

# include <algorithm>
//# include "iterator.hpp"

namespace ft 
{
	/*template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2)
	{
		return (lexicographical_compare(first1, last1, first2, last2,
											std::__less<typename iterator_traits<InputIterator1>::value_type,
													typename iterator_traits<InputIterator2>::value_type>()));
	}
	
	template <class Compare, class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		return (false);
	}*/

	template <class T>
	void swap(T &a, T &b)
	{
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}

	template <bool, class _Tp = void> struct enable_if {};
	template <class _Tp> struct enable_if<true, _Tp> 
	{
		typedef _Tp type;
	};

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2)
	{
		for (; first2 != last2; ++first1, (void) ++first2)
		{
			if (first1 == last1 || *first1 < *first2)
				return (true);
			if (*first2 < *first1)
				return (false);
		}
		return (false);
	}

	/*template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		typedef typename iterator_traits<InputIterator1>::value_type v1;
		typedef typename iterator_traits<InputIterator2>::value_type v2;
		return equal(first1, last1, first2, std::equal_to<v1, v2>());
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!pred(*first1, *first2))
				return (false);
		return (true);
	}*/
	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, (void) ++first2)
			if (!(*first1 == *first2))
				return (false);
		return (true);
	}
};

#endif