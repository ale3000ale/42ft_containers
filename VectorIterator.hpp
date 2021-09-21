/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:15:47 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/21 19:30:00 by amarcell         ###   ########.fr       */
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
		VectorIterator(VectorIterator const & other) : ptr(other.ptr) {}
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

	// constant element but u can modify the pointer (read only)
	template <typename T>
	class ConstVectorIterator
	{
	protected:
		T const *ptr;
	
	public:
		ConstVectorIterator() : ptr(NULL) {}
		ConstVectorIterator(T const *_ptr) : ptr(_ptr){}
		ConstVectorIterator(ConstVectorIterator const & other) : ptr(other.ptr) {}
		virtual ~ConstVectorIterator(){}

		ConstVectorIterator & operator=(ConstVectorIterator const & other)
		{
			ptr = other.ptr;
			return (*this);
		}
		virtual ConstVectorIterator & operator++()
		{
			ptr++;
			return (*this);
		}
		virtual ConstVectorIterator & operator--()
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

		virtual T  operator[](size_t n) const
		{
			return (ptr[n]);
		}
		virtual ConstVectorIterator operator+(int n) const
		{
			ConstVectorIterator tmp(*this);
			tmp.ptr += n;
			return (tmp);
		}
		virtual ConstVectorIterator operator-(int n) const
		{
			ConstVectorIterator tmp(*this);
			tmp.ptr -= n;
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
			ReverseVectorIterator() : VectorIterator<T>() {}
			ReverseVectorIterator(T * _ptr) : VectorIterator<T>(_ptr){}
			ReverseVectorIterator(ReverseVectorIterator const & other) : VectorIterator<T>(other){}
			ReverseVectorIterator(ConstReverseVectorIterator<T> other) : VectorIterator<T>(other){}
			~ReverseVectorIterator(){}
			
			VectorIterator<T> & operator++()
			{
				return (VectorIterator<T>::operator--());
			}	
			VectorIterator<T> & operator--()
			{
				return (VectorIterator<T>::operator++());
			}
			
			T  operator[](size_t n) 
			{
				return (*(this->ptr - n));
			}
			
			VectorIterator<T> operator+(int n) const
			{
				return (VectorIterator<T>::operator-(n));
			}
			VectorIterator<T> operator-(int n) const
			{
				return (VectorIterator<T>::operator+(n));
			}
	};


	template <typename T>
	class ConstReverseVectorIterator: public ConstVectorIterator<T>
	{
		
		public:
			ConstReverseVectorIterator() : ConstVectorIterator<T>() {}
			ConstReverseVectorIterator(T const *_ptr) : ConstVectorIterator<T>(_ptr){}
			ConstReverseVectorIterator(ConstReverseVectorIterator const & other) : ConstVectorIterator<T>(other){}
			~ConstReverseVectorIterator(){}
			
			ConstVectorIterator<T> & operator++()
			{
				return (ConstVectorIterator<T>::operator--());
			}	
			ConstVectorIterator<T> & operator--()
			{
				return (ConstVectorIterator<T>::operator++());
			}
			
			T  operator[](size_t n) const
			{
				return (*(this->ptr - n));
			}
			
			ConstVectorIterator<T> operator+(int n) const
			{
				return (ConstVectorIterator<T>::operator-(n));
			}
			ConstVectorIterator<T> operator-(int n) const
			{
				return (ConstVectorIterator<T>::operator+(n));
			}
	};

};

#endif