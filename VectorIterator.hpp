/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/23 17:20:39 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_H__
# define VECTORITERATOR_H__

# include "iterator.hpp"

namespace ft
{
	template <class T, class Allocator>
	class vector;

	template <class _Iter> // _Iter = T*
	class VectorIterator
	{
		private:
			_Iter	ptr;

		public:
			typedef _Iter														iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;

			/*-------------------CONSTRUCTURS-------------------*/
			VectorIterator() : ptr(nullptr) {}
			VectorIterator(VectorIterator<iterator_type> const & other) : ptr(other.ptr) {}
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
	};

	/*---------LOGIC OPERATOR---------*/
	//prototype because they nedd only 2 parameters
	template <class _Iter1, class _Iter2>
	bool operator==(const VectorIterator<_Iter1>& vc1, const VectorIterator<_Iter2>& vc2)
	{
		return (vc1.base() == vc2.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator<(const VectorIterator<_Iter1>& vc1, const VectorIterator<_Iter2>& vc2)
	{
		return (vc1.base() < vc2.base());
	}

	template <class _Iter1, class _Iter2>
	bool operator!=(const VectorIterator<_Iter1>& vc1, const VectorIterator<_Iter2>& vc2)
	{
		return !(vc1.base() == vc2.base());
	}
				
	template <class _Iter1, class _Iter2>
	bool operator>(const VectorIterator<_Iter1>& vc1, const VectorIterator<_Iter2>& vc2)
	{
		return (vc1.base() > vc2.base());
	}
				
	template <class _Iter1, class _Iter2>
	bool operator>=(const VectorIterator<_Iter1>& vc1, const VectorIterator<_Iter2>& vc2)
	{
		return (vc1.base() >= vc2.base());
	}
					
	template <class _Iter1, class _Iter2>
	bool operator<=(const VectorIterator<_Iter1>& vc1, const VectorIterator<_Iter2>& vc2)
	{
		return (vc1.base() <= vc2.base());
	}
};

#endif