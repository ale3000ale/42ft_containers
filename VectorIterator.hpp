/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/16 19:44:25 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_H__
#define VECTORITERATOR_H__

namespace ft
{
	template <typename T>
	class ConstVectorIterator;
	template <typename T>
	class ConstReverseVectorIterator;

	template <typename T>
	class VectorIterator
	{
	protected:
		T * ptr;
	
	public:
		VectorIterator() : ptr(NULL) {}
		VectorIterator(T * _ptr) : ptr(_ptr){}
		VectorIterator(VectorIterator const & other)
		{
			*this = other;
		}
		VectorIterator(ConstVectorIterator<T> other)ptr(other.ptr()){}
		~VectorIterator(){}

		
		
	};
}

#endif