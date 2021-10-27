/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/28 16:36:30 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template <class T, class Allocator>
	class vector;

	template <class Iter> // _Iter = T*
	class VectorIterator
	{
		private:
			Iter	ptr;

		public:
			typedef Iter														iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;

			/*-------------------CONSTRUCTURS-------------------*/
			VectorIterator() : ptr(nullptr) {}
			template <class U>
				VectorIterator(VectorIterator<U> const & other) : ptr(other.ptr) {}
			~VectorIterator(){}

			/*-------------------OPERATORS-------------------*/
			VectorIterator & operator=(VectorIterator const & other)
			{
				ptr = other.ptr;
				return (*this);
			}
		private:
			VectorIterator(iterator_type _ptr) : ptr(_ptr){}
			/*---------ACCESS OPERATOR---------*/
		public:
			reference operator*() const
			{
				return (*ptr);
			}
			pointer operator->() const
			{
				return (ptr);
			}
			reference  operator[](size_t n) const
			{
				return (ptr[n]);
			}
			/*---------ARITMETIC OPERATOR---------*/
			VectorIterator & operator++()
			{
				++ptr;
				return (*this);
			}
			VectorIterator & operator--()
			{
				--ptr;
				return (*this);
			}
			VectorIterator operator++(int)
			{
				VectorIterator tmp(*this);
				operator++();
				return (tmp);
			}
			VectorIterator operator--(int)
			{
				VectorIterator tmp(*this);
				operator--();
				return (tmp);
			}
			VectorIterator operator+(difference_type n) const
			{
				VectorIterator tmp(*this);
				tmp += n;
				return (tmp);
			}
			VectorIterator operator-(difference_type n) const
			{
				VectorIterator tmp(*this);
				tmp -= n;
				return (tmp);
			}
			VectorIterator & operator+=(difference_type n)
			{
				ptr += n;
				return (*this);
			}
			VectorIterator & operator-=(difference_type n)
			{
				ptr -= n;
				return (*this);
			}

			/*-------------------ACCESSOR-------------------*/
			iterator_type base() const
			{
				return (ptr);
			}
		template <class T, class Allocator> friend class vector;
		template <class U> friend class VectorIterator;
	};

	/*---------LOGIC OPERATOR---------*/
	template <class Iter1, class Iter2>
	bool operator==(const VectorIterator<Iter1>& vc1, const VectorIterator<Iter2>& vc2)
	{
		return (vc1.base() == vc2.base());
	}

	template <class Iter1, class Iter2>
	bool operator<(const VectorIterator<Iter1>& vc1, const VectorIterator<Iter2>& vc2)
	{
		return (vc1.base() < vc2.base());
	}

	template <class Iter1, class Iter2>
	bool operator!=(const VectorIterator<Iter1>& vc1, const VectorIterator<Iter2>& vc2)
	{
		return !(vc1.base() == vc2.base());
	}
				
	template <class Iter1, class Iter2>
	bool operator>(const VectorIterator<Iter1>& vc1, const VectorIterator<Iter2>& vc2)
	{
		return (vc1.base() > vc2.base());
	}
				
	template <class Iter1, class Iter2>
	bool operator>=(const VectorIterator<Iter1>& vc1, const VectorIterator<Iter2>& vc2)
	{
		return (vc1.base() >= vc2.base());
	}
					
	template <class Iter1, class Iter2>
	bool operator<=(const VectorIterator<Iter1>& vc1, const VectorIterator<Iter2>& vc2)
	{
		return (vc1.base() <= vc2.base());
	}

	template <class Iter1, class Iter2>
	typename VectorIterator<Iter1>::difference_type operator-(const VectorIterator<Iter1>& left, const VectorIterator<Iter2>& right) {
		return (left.base() - right.base());
	}
	template <class Iter1, class Iter2>
	typename VectorIterator<Iter1>::difference_type operator+(const VectorIterator<Iter1>& left, const VectorIterator<Iter2>& right) {
		return (left.base() + right.base());
	}
	template <class Iter>
	VectorIterator<Iter> operator-(typename VectorIterator<Iter>::difference_type left, const VectorIterator<Iter>& right) {
		return (right - left);
	}
	template <class Iter>
	VectorIterator<Iter> operator+(typename VectorIterator<Iter>::difference_type left, const VectorIterator<Iter>& right) {
		return (right + left);
	}
};

#endif