/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/23 12:53:29 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_H__
# define VECTORITERATOR_H__

# include "iterator.hpp"

namespace ft
{
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
			VectorIterator(iterator_type _ptr) : ptr(_ptr){}
			VectorIterator(VectorIterator<iterator_type> const & other) : ptr(other.ptr) {}
			~VectorIterator(){}

			VectorIterator & operator=(VectorIterator const & other)
			{
				ptr = other.ptr;
				return (*this);
			}
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
			bool operator==(VectorIterator const & other) const
			{
				return (ptr == other.ptr);
			}
			bool operator!=(VectorIterator const & other) const
			{
				return (ptr != other.ptr);
			}
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
			/*-------------------OPERATORS-------------------*/
			/*---------ACCESS OPERATOR---------*/
			/*---------ARITMETIC OPERATOR---------*/
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

			/*-------------------METHODS-------------------*/
			
		

			/*-------------------ACCESSOR-------------------*/
			iterator_type base() const
			{
				return (ptr);
			}
	};
};

#endif