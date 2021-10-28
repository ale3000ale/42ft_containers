

#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t
#include <iostream>

namespace ft
{
	// define the traits of iterator from an iterator
	template<class Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
		};

	// define the traits of iterator from a Class
	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// define the iterator mask traits
	template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

/*-------------------------------------REVERSE ITERATOR-------------------------------------*/

	//standard reverse iterator
	template <class _Iter>
	class reverse_iterator: // use iterator mask traits
							public iterator<typename iterator_traits<_Iter>::iterator_category,
											typename iterator_traits<_Iter>::value_type,
											typename iterator_traits<_Iter>::difference_type,
											typename iterator_traits<_Iter>::pointer,
											typename iterator_traits<_Iter>::reference>
	{
	protected:
		_Iter it;
	public:
		typedef _Iter                                            iterator_type;
		typedef typename iterator_traits<_Iter>::difference_type difference_type;
		typedef typename iterator_traits<_Iter>::reference       reference;
		typedef typename iterator_traits<_Iter>::pointer         pointer;

		/*-------------------CONSTRUCTURS-------------------*/
		reverse_iterator() : it() {}
		explicit reverse_iterator(_Iter _it) :  it(_it) {}
		//constructur copy
		template <class _BaseIt>	//base iterator of the copy RI
        reverse_iterator(const reverse_iterator<_BaseIt>& cpy) 
													:  it(cpy.base()) {}

		/*-------------------OPERATORS-------------------*/
		/* call operators from base_iterator */
		template <class _BaseIt>	//base iterator of the copy RI
		reverse_iterator& operator=(const reverse_iterator<_BaseIt>& cpy)
		{
			it = cpy.base(); 
			return (*this);
		}

		/*---------ACCESS OPERATOR---------*/
		reference operator*() const 
		{
			iterator_type tmp = it;
			return (*(--tmp));
		}

		pointer  operator->() const 
		{
			return (&operator*());
		}

		reference			operator[](difference_type n) const 
		{
			return *(*this + n);
		}

		/*---------ARITMETIC OPERATOR---------*/
		reverse_iterator&	operator++() 
		{
			--it; 
			return *this;
		}
		reverse_iterator	operator++(int) 
		{
			reverse_iterator tmp(*this);
			--it;
			return tmp;
		}
		
		reverse_iterator&	operator--() 
		{
			++it;
			return *this;
		}

		reverse_iterator	operator--(int) 
		{
			reverse_iterator tmp(*this);
			++it;
			return tmp;
		}

		reverse_iterator	operator+(difference_type n) const 
		{
			return reverse_iterator(it - n);
		}

		reverse_iterator&	operator+=(difference_type n) 
		{
			it -= n;
			return *this;
		}

		reverse_iterator	operator-(difference_type n) const 
		{
			return reverse_iterator(it + n);
		}

		reverse_iterator&	operator-=(difference_type n) 
		{
			it += n;
			return *this;
		}

		/*-------------------ACCESSOR-------------------*/

		_Iter base() const 
		{
			return it;
		}
	}; // class reverse_iterator

	/*---------LOGIC OPERATOR---------*/
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() == y.base());
	}

	template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() > y.base());
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() != y.base());
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() < y.base());
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() <= y.base());
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (x.base() >= y.base());
	}

	template <class Iter1, class Iter2>
	typename reverse_iterator<Iter1>::difference_type operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
	{
		return (y.base() - x.base());
	}

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& x)
	{
		return (reverse_iterator<Iter>(x.base() - n));
	}
}; // namespace ft

#endif