/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/21 16:33:38 by amarcell         ###   ########.fr       */
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
		VectorIterator(ConstVectorIterator<T> other) : ptr(other.ptr()){}
		virtual ~VectorIterator(){}

		VectorIterator & operator=(VectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		}
		virtual VectorIterator & operator++()
		{
			ptr++;
			return (*this);
		}
		virtual VectorIterator & operator--()
		{
			ptr--;
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
		T & operator*()
		{
			return (*ptr);
		}
		T * operator->()
		{
			return (*ptr);
		}

		virtual T  operator[](size_t n)
		{
			return (ptr[n]);
		}
		virtual VectorIterator operator+(int n) const
		{
			VectorIterator tmp(*this);
			tmp.ptr += n;
			return (tmp);
		}
		virtual VectorIterator operator-(int n) const
		{
			VectorIterator tmp(*this);
			tmp.ptr -= n;
			return (tmp);
		}
		 VectorIterator & operator+=(int n)
		{
			*this = *this + n;
			return (*this);
		}
		VectorIterator & operator-=(int n)
		{
			*this = *this - n;
			return (*this);
		}
	};


	template <typename T>
	class ConstVectorIterator
	{
	protected:
		const T * ptr;
	
	public:
		ConstVectorIterator() : ptr(NULL) {}
		ConstVectorIterator(T * _ptr) : ptr(_ptr){}
		~ConstVectorIterator(){}

		ConstVectorIterator & operator=(ConstVectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		}
		ConstVectorIterator & operator++()
		{
			ptr++;
			return (*this);
		}
		ConstVectorIterator & operator--()
		{
			ptr--;
			return (*this);
		}
		ConstVectorIterator operator++(int)
		{
			ConstVectorIterator tmp(*this);
			operator++();
			return (tmp);
		}
		ConstVectorIterator operator--(int)
		{
			ConstVectorIterator tmp(*this);
			operator--();
			return (tmp);
		}
		bool operator==(ConstVectorIterator const & other) const
		{
			return (ptr == other.ptr);
		}
		bool operator!=(ConstVectorIterator const & other) const
		{
			return (ptr != other.ptr);
		}
		T & operator*() const
		{
			return (*ptr);
		}
		T * operator->() const
		{
			return (*ptr);
		}

		T  operator[](size_t n) const
		{
			return (ptr[n]);
		}
		ConstVectorIterator operator+(int n) const
		{
			ConstVectorIterator tmp(*this);
			tmp += n;
			return (tmp);
		}
		ConstVectorIterator operator-(int n) const
		{
			ConstVectorIterator tmp(*this);
			tmp -= n;
			return (tmp);
		}
		ConstVectorIterator & operator+=(int n)
		{
			*this = *this + n;
			return (*this);
		}
		ConstVectorIterator & operator-=(int n)
		{
			*this = *this - n;
			return (*this);
		}
	};

	template <typename T>
	class ReverseVectorIterator: public VectorIterator<T>
	{
		
		public:
			ReverseVectorIterator() : VectorIterator() {}
			ReverseVectorIterator(T * _ptr) : VectorIterator(_ptr){}
			ReverseVectorIterator(ReverseVectorIterator const & other) : VectorIterator(other){}
			ReverseVectorIterator(ConstReverseVectorIterator<T> other) : VectorIterator(other){}
			~ReverseVectorIterator(){}
			
			VectorIterator<T> & operator++()
			{
				return (VectorIterator::operator--());
			}	
			VectorIterator & operator--()
			{
				return (VectorIterator::operator++());
			}
			
			T  operator[](size_t n) 
			{
				return (*(ptr - n));
			}
			
			VectorIterator operator+(int n) const
			{
				return (VectorIterator::operator-(n));
			}
			VectorIterator operator-(int n) const
			{
				return (VectorIterator::operator+(n));
			}
	};


	template <typename T>
	class ConstReverseVectorIterator
	{
	protected:
		 T * ptr;
		
	public:
		ConstReverseVectorIterator()
		{}
		ConstReverseVectorIterator(const ConstReverseVectorIterator & other)
		{
			*this = other;
		}
		ConstReverseVectorIterator(T * _ptr)
		{
			ptr = _ptr;
		}
		~ConstReverseVectorIterator()
		{}
		ConstReverseVectorIterator & operator=(ConstReverseVectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		}
		ConstReverseVectorIterator & operator++()
		{
			ptr--;
			return (*this);
		}
		ConstReverseVectorIterator & operator--()
		{
			ptr++;
			return (*this);
		}
		ConstReverseVectorIterator operator++(int)
		{
			ConstReverseVectorIterator tmp(*this);
			operator++();
			return (tmp);
		}
		ConstReverseVectorIterator operator--(int)
		{
			ConstReverseVectorIterator tmp(*this);
			operator--();
			return (tmp);
		}
		bool operator==(const ConstReverseVectorIterator & other) const
		{
			return (ptr == other.ptr);
		}
		bool operator!=(const ConstReverseVectorIterator & other) const
		{
			return (ptr != other.ptr);
		}
		T & operator*()	const
		{
			return (*ptr);
		}
		T *operator->()	const
		{
			return (*ptr);
		}
		T  operator[](size_t n) const
		{
			return (*(ptr - n));
		}
		ConstReverseVectorIterator operator+(int n) const
		{
			ConstReverseVectorIterator tmp(*this);
			tmp += n;
			return (tmp);
		}
		ConstReverseVectorIterator operator-(int n) const
		{
			ConstReverseVectorIterator tmp(*this);
			tmp -= n;
			return (tmp);
		}
		ConstReverseVectorIterator & operator+=(int n)
		{
			*this = *this - n;
			return (*this);
		}
		ConstReverseVectorIterator & operator-=(int n)
		{
			*this = *this + n;
			return (*this);
		}
	};
};

#endif