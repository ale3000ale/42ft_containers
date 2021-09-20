/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/20 17:07:01 by amarcell         ###   ########.fr       */
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

		VectorIterator & operator=(VectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		};
		VectorIterator & operator++()
		{
			ptr++;
			return (*this);
		};
		VectorIterator & operator--()
		{
			ptr--;
			return (*this);
		};
		VectorIterator operator++(int)
		{
			VectorIterator tmp(*this);
			operator++();
			return (tmp);
		};
		VectorIterator operator--(int)
		{
			VectorIterator tmp(*this);
			operator--();
			return (tmp);
		};
		bool operator==(VectorIterator const & other) const
		{
			return (ptr == other.ptr);
		};
		bool operator!=(VectorIterator const & other) const
		{
			return (ptr != other.ptr);
		};
		T & operator*()
		{
			return (*ptr);
		};
		T * operator->()
		{
			return (*ptr);
		};
		VectorIterator operator+(int n) const
		{
			VectorIterator tmp(*this);
			tmp += n;
			return (tmp);
		};
		VectorIterator operator-(int n) const
		{
			VectorIterator tmp(*this);
			tmp -= n;
			return (tmp);
		};
		VectorIterator & operator+=(int n)
		{
			*this = *this + n;
			return (*this);
		};
		VectorIterator & operator-=(int n)
		{
			*this = *this - n;
			return (*this);
		};
	};


	template <typename T>
	class ConstVectorIterator
	{
	protected:
		T * ptr;
	
	public:
		ConstVectorIterator() : ptr(NULL) {}
		ConstVectorIterator(T * _ptr) : ptr(_ptr){}
		~VectorIterator(){}

		ConstVectorIterator & operator=(ConstVectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		};
		ConstVectorIterator & operator++()
		{
			ptr++;
			return (*this);
		};
		ConstVectorIterator & operator--()
		{
			ptr--;
			return (*this);
		};
		ConstVectorIterator operator++(int)
		{
			ConstVectorIterator tmp(*this);
			operator++();
			return (tmp);
		};
		ConstVectorIterator operator--(int)
		{
			ConstVectorIterator tmp(*this);
			operator--();
			return (tmp);
		};
		bool operator==(ConstVectorIterator const & other) const
		{
			return (ptr == other.ptr);
		};
		bool operator!=(ConstVectorIterator const & other) const
		{
			return (ptr != other.ptr);
		};
		T & operator*() const
		{
			return (*ptr);
		};
		T * operator->() const
		{
			return (*ptr);
		};
		ConstVectorIterator operator+(int n) const
		{
			ConstVectorIterator tmp(*this);
			tmp += n;
			return (tmp);
		};
		ConstVectorIterator operator-(int n) const
		{
			ConstVectorIterator tmp(*this);
			tmp -= n;
			return (tmp);
		};
		ConstVectorIterator & operator+=(int n)
		{
			*this = *this + n;
			return (*this);
		};
		ConstVectorIterator & operator-=(int n)
		{
			*this = *this - n;
			return (*this);
		};
	};

	template <typename T>
	class ReverseVectorIterator
	{
	protected:
		T * ptr;
		
	public:
		ReverseVectorIterator()
		{};
		ReverseVectorIterator(const ReverseVectorIterator & other)
		{
			*this = other;
		};
		ReverseVectorIterator(T * _ptr)
		{
			ptr = _ptr;
		};
		ReverseVectorIterator(ReverseVectorIterator<T> other)
		{
			ptr = other.ptr();
		};
		~ReverseVectorIterator()
		{};
		ReverseVectorIterator & operator=(ReverseVectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		};
		ReverseVectorIterator & operator++()
		{
			ptr--;
			return (*this);
		};
		ReverseVectorIterator & operator--()
		{
			ptr++;
			return (*this);
		};
		ConstReverseVectorIterator operator++(int)
		{
			ConstReverseVectorIterator tmp(*this);
			operator++();
			return (tmp);
		};
		ReverseVectorIterator operator--(int)
		{
			ReverseVectorIterator tmp(*this);
			operator--();
			return (tmp);
		};
		bool operator==(const ReverseVectorIterator & other) const
		{
			return (ptr == other.ptr);
		};
		bool operator!=(const ReverseVectorIterator & other) const
		{
			return (ptr != other.ptr);
		};
		T & operator*()
		{
			return (*ptr);
		};
		T *operator->()
		{
			return (*ptr);
		};
		ReverseVectorIterator operator+(int n) const
		{
			ReverseVectorIterator tmp(*this);
			tmp += n;
			return (tmp);
		};
		ReverseVectorIterator operator-(int n) const
		{
			ReverseVectorIterator tmp(*this);
			tmp -= n;
			return (tmp);
		};
		ReverseVectorIterator & operator+=(int n)
		{
			*this = *this - n;
			return (*this);
		};
		ReverseVectorIterator & operator-=(int n)
		{
			*this = *this + n;
			return (*this);
		};
	};


	template <typename T>
	class ConstReverseVectorIterator
	{
	protected:
		T * ptr;
		
	public:
		ConstReverseVectorIterator()
		{};
		ConstReverseVectorIterator(const ConstReverseVectorIterator & other)
		{
			*this = other;
		};
		ConstReverseVectorIterator(T * _ptr)
		{
			ptr = _ptr;
		};
		~ConstReverseVectorIterator()
		{};
		ConstReverseVectorIterator & operator=(ConstReverseVectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		};
		ConstReverseVectorIterator & operator++()
		{
			ptr--;
			return (*this);
		};
		ConstReverseVectorIterator & operator--()
		{
			ptr++;
			return (*this);
		};
		ConstReverseVectorIterator operator++(int)
		{
			ConstReverseVectorIterator tmp(*this);
			operator++();
			return (tmp);
		};
		ConstReverseVectorIterator operator--(int)
		{
			ConstReverseVectorIterator tmp(*this);
			operator--();
			return (tmp);
		};
		bool operator==(const ConstReverseVectorIterator & other) const
		{
			return (ptr == other.ptr);
		};
		bool operator!=(const ConstReverseVectorIterator & other) const
		{
			return (ptr != other.ptr);
		};
		T & operator*()	const
		{
			return (*ptr);
		};
		T *operator->()	const
		{
			return (*ptr);
		};
		ConstReverseVectorIterator operator+(int n) const
		{
			ConstReverseVectorIterator tmp(*this);
			tmp += n;
			return (tmp);
		};
		ConstReverseVectorIterator operator-(int n) const
		{
			ConstReverseVectorIterator tmp(*this);
			tmp -= n;
			return (tmp);
		};
		ConstReverseVectorIterator & operator+=(int n)
		{
			*this = *this - n;
			return (*this);
		};
		ConstReverseVectorIterator & operator-=(int n)
		{
			*this = *this + n;
			return (*this);
		};
	};
}

#endif