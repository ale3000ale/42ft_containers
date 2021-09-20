/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:07:53 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/20 19:11:47 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H__
#define VECTOR_H__

#include "VectorIterator.hpp"
#include <iostream>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class Vector
	{
	private:
		T value_type;
		Alloc
	public:
		Vector();
		~Vector();
	};
	
	Vector::Vector(/* args */)
	{
	}
	
	Vector::~Vector()
	{
	}
	
}

#endif