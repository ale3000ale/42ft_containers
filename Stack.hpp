/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:06:54 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/28 01:07:16 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_H
# define VECTORITERATOR_H

# include "iterator.hpp"
# include "util.h"
# include <iostream>
# include <stack>

namespace ft
{

	template <class Tp, class _Container>
	class stack
	{
		public:
			typedef _Container                               container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::reference       reference;
			typedef typename container_type::const_reference const_reference;
			typedef typename container_type::size_type       size_type;

			//tp must be equal to container type for make an object stack
			//static assert if the condition in static_assert is false generate a compling error
			static_assert( (std::is_same<Tp, value_type>::value) ,
							 "Stack need object type equal to contener type (-.-\")" ); 
			
		protected:
			/*-------------------ATTRIBUTES-------------------*/
			container_type c;

		public:
			/*-------------------CONSTRUCTURS-------------------*/
			stack() : c() {}
			explicit stack(const container_type& _c) : c(_c) {}
			stack(const stack& st) : c(st.c) {}

			template <class _Alloc>
			explicit stack(const _Alloc& a): c(a) {}
			
			template <class _Alloc>
			stack(const container_type& c, const _Alloc& a): c(c, a) {}

			template <class _Alloc>
			stack(const stack& s, const _Alloc& a): c(s.c, a) {}

	
			stack& operator=(const stack& st)
			{
				c = st.c;
				return *this;
			}

			bool empty()     const      
			{
				return (c.empty());
			}
			
			size_type size() const
			{
				return (c.size());
			}
			
			reference top()
			{
				return c.back();
			}
			
			const_reference top() const 
			{
				return c.back();
			}

			void push(const value_type& v)
			{
				c.push_back(v);
			}
			
			void pop() 
			{
				c.pop_back();
			}

			//TODO: check swap if just exist or need a definition
			void swap(stack& s)
			{
				c.swap(s.c);
			}

			template <class T1, class _C1>
			friend
			bool
			operator==(const stack<T1, _C1>& x, const stack<T1, _C1>& y);

			template <class T1, class _C1>
			friend
			bool
			operator< (const stack<T1, _C1>& x, const stack<T1, _C1>& y);
	};


	/*-------------------OPERATORS-------------------*/
			/*---------LOGIC OPERATOR---------*/

	template <class Tp, class _Container> //base op
	bool	operator==(const stack<Tp, _Container>& x, const stack<Tp, _Container>& y)
	{
		return x.c == y.c;
	}

	template <class Tp, class _Container> //base op
	bool	operator< (const stack<Tp, _Container>& x, const stack<Tp, _Container>& y)
	{
		return x.c < y.c;
	}

	template <class Tp, class _Container>
	bool	operator!=(const stack<Tp, _Container>& x, const stack<Tp, _Container>& y)
	{
		return !(x == y);
	}

	template <class Tp, class _Container>
	bool	operator> (const stack<Tp, _Container>& x, const stack<Tp, _Container>& y)
	{
		return y < x;
	}

	template <class Tp, class _Container>
	bool	operator>=(const stack<Tp, _Container>& x, const stack<Tp, _Container>& y)
	{
		return !(x < y);
	}

	template <class Tp, class _Container>
	bool	operator<=(const stack<Tp, _Container>& x, const stack<Tp, _Container>& y)
	{
		return !(y < x);
	}

	
};



#endif