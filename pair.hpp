
#ifndef PAIR_H__
# define PAIR_H__

# include <algorithm>
//# include "iterator.hpp"
#include "utils.hpp"

namespace ft 
{
	template <class T1, class T2>
	struct pair		//default public
	{
		typedef T1	first_type;
		typedef T2	second_type;
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

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 __x, T2 __y)
	{
		return pair<T1, T2>(__x, __y);
	}

	template <class _T1, class _T2>
	bool operator==(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
	{
		return __x.first == __y.first && __x.second == __y.second;
	}

	template <class _T1, class _T2>
	bool operator!=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
	{
		return !(__x == __y);
	}

	template <class _T1, class _T2>
	bool operator< (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
	{
		return __x.first < __y.first || (!(__y.first < __x.first) && __x.second < __y.second);
	}

	template <class _T1, class _T2>
	bool operator> (const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
	{
		return __y < __x;
	}

	template <class _T1, class _T2>
	bool operator>=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
	{
		return !(__x < __y);
	}

	template <class _T1, class _T2>
	bool operator<=(const pair<_T1,_T2>& __x, const pair<_T1,_T2>& __y)
	{
		return !(__y < __x);
	}

	template <class _T1, class _T2>
	typename enable_if
	<	std::__is_swappable<_T1>::value &&
		std::__is_swappable<_T2>::value,
		void > ::type
		
	swap (pair<_T1, _T2>& __x, pair<_T1, _T2>& __y)
	{
		__x.swap(__y);
	}
};

#endif