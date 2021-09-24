/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:06:54 by amarcell          #+#    #+#             */
/*   Updated: 2021/09/24 18:04:30 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_H
# define VECTORITERATOR_H

# include "iterator.hpp"
# include <stack>

namespace ft
{

	template <bool, class _Tp = void> struct enable_if {};
	template <class _Tp> struct enable_if<true, _Tp> {typedef _Tp type;};

	template <class Tp, class _Container>
	class _LIBCPP_TEMPLATE_VIS stack
	{
		public:
			typedef _Container                               container_type;
			typedef typename container_type::value_type      value_type;
			typedef typename container_type::reference       reference;
			typedef typename container_type::const_reference const_reference;
			typedef typename container_type::size_type       size_type;
			static_assert((is_same<_Tp, value_type>::value), "" );
			
			
		protected:
			/*-------------------ATTRIBUTES-------------------*/
			container_type c;

		public:
			/*-------------------CONSTRUCTURS-------------------*/
			stack() : c() {}
			explicit stack(const container_type& _c) : c(_c) {}
			stack(const stack& st) : c(st.c) {}

			stack& operator=(const stack& st)
			{
				c = st.c;
				return *this;
			}
			


			//TODO: check this constructor
			template <class _Alloc>
				explicit stack(const _Alloc& a,
							typename enable_if<uses_allocator<container_type,
																_Alloc>::value>::type* = 0)
					: c(a) {}
			template <class _Alloc>
				stack(const container_type& c, const _Alloc& a,
					typename enable_if<uses_allocator<container_type,
														_Alloc>::value>::type* = 0)
					: c(c, a) {}
			template <class _Alloc>
				stack(const stack& s, const _Alloc& a,
					typename enable_if<uses_allocator<container_type,
														_Alloc>::value>::type* = 0)
					: c(s.c, a) {}



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

	template <class _Tp, class _Container> //base op
	bool	operator==(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{
		return x.c == y.c;
	}

	template <class _Tp, class _Container> //base op
	bool	operator< (const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{
		return x.c < y.c;
	}

	template <class _Tp, class _Container>
	bool	operator!=(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{
		return !(x == y);
	}

	template <class _Tp, class _Container>
	bool	operator> (const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{
		return y < x;
	}

	template <class _Tp, class _Container>
	bool	operator>=(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{
		return !(x < y);
	}

	template <class _Tp, class _Container>
	bool	operator<=(const stack<_Tp, _Container>& x, const stack<_Tp, _Container>& y)
	{
		return !(y < x);
	}
};

#endif