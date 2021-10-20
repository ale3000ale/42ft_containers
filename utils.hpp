
#ifndef UTILS_HPP
# define UTILS_HPP

# include <algorithm>
# include "iterator.hpp"

namespace ft 
{
	/*template <class T>
	void swap(T &a, T &b)
	{
		T tmp;
		tmp = a;
		a = b;
		b = tmp;
	}*/

	template <class T, T v>
	struct integral_constant
	{
		static const T				value = v;
		typedef T					value_type;
		typedef integral_constant	type;
		operator value_type() const
			{ return (value); }
	};

	#define BOOL_CONST(b) integral_constant<bool, b>

	typedef BOOL_CONST(true)	true_type;
	typedef BOOL_CONST(false)	false_type;
	
	template <class T>	struct is_integral_base                     : public false_type {};
	template <>			struct is_integral_base<bool>               : public true_type {};
	template <>			struct is_integral_base<char>               : public true_type {};
	template <>			struct is_integral_base<signed char>        : public true_type {};
	template <>			struct is_integral_base<unsigned char>      : public true_type {};
	template <>			struct is_integral_base<wchar_t>            : public true_type {};
	template <>			struct is_integral_base<short>              : public true_type {};
	template <>			struct is_integral_base<unsigned short>     : public true_type {};
	template <>			struct is_integral_base<int>                : public true_type {};
	template <>			struct is_integral_base<unsigned int>       : public true_type {};
	template <>			struct is_integral_base<long>               : public true_type {};
	template <>			struct is_integral_base<unsigned long>      : public true_type {};
	template <>			struct is_integral_base<long long>          : public true_type {};
	template <>			struct is_integral_base<unsigned long long> : public true_type {};

	template <class T>
	struct is_integral : public is_integral_base<T> {};

	template <bool, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T> 
	{
		typedef T type;
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