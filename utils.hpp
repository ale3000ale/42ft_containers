
#ifndef UTILS_HPP
# define UTILS_HPP

# include <algorithm>
# include "iterator.hpp"

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

	template <class Compare, class InputIterator1, class InputIterator2>
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

	/*template <class _InputIterator1, class _InputIterator2>
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

	template <class T1, class T2>
	struct pair		//default public
	{
		/*-------------------ATTRIBUTS-------------------*/
		T1 first;
		T2 second;

		/*-------------------CONSTRUCTURS-------------------*/
		pair() : first(), second() {}		
		pair(T1 const& _t1, T2 const& _t2) : first(_t1), second(_t2) {}

		template <class _U1, class _U2>
		pair(const pair<_U1, _U2>& _p) : first(_p.first), second(_p.second) {}

		/*-------------------ASSIGN OPERATOR-------------------*/
		pair& operator=(pair const& _p) 
		{
			first = _p.first;
			second = _p.second;
			return *this;
		}

		/*-------------------METHODS-------------------*/
		void	swap(pair& __p)
		{
			ft::swap(first,  __p.first);
			ft::swap(second, __p.second);
		}
	};

	template <class T1, class T2>
	std::ostream &operator<<(std::ostream &out, pair<T1, T2> &p)
	{
		out <<"<";
		out << p.first << " : " << p.second;
		out << ">";
		return (out);
	}
};

#endif