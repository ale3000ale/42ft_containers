/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:11:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/10/22 22:55:46 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H__
# define NODE_H__

# include "utils.hpp"
# include <memory> // for std::allocator

namespace ft
{
	# define COLOR_OFF			"\033[0m"
	# define BBLACK				"\033[1;30m"    
	# define BRED				"\033[1;31m"        
	# define BWHITE				"\033[1;37m"

	template <class _Tp>
	class binary_node
	{
		public:

			typedef class binary_node<_Tp>			__node_type;
			typedef class binary_node<_Tp>*			__node_type_pointer;
			typedef _Tp								__value_type;

			__value_type						*_value;
			__node_type_pointer					left;
			__node_type_pointer					right;
			__node_type_pointer         		parent;
			bool								color;

			void __set_parent(__node_type_pointer _p)
			{
				parent = _p;
			}
			__value_type& value()
			{ return(*this->_value); };

		public:
			binary_node(): 
				_value(nullptr), left(nullptr), right(nullptr), parent(nullptr), color(false)
			{}

			binary_node(__value_type *_content) : 
				_value(_content), left(nullptr), right(nullptr), parent(nullptr), color(false)
			{}

			binary_node(__node_type_pointer _parent): parent(_parent), color(false)
			{
			}

			binary_node(__value_type *_content, __node_type &_parent) : 
				_value(_content), parent(&_parent), color(false)
			{}

			binary_node(__value_type *_content, __node_type &_parent, __node_type &_left, __node_type &_right) : 
				_value(_content), left(&_left), right(&_right), parent(&_parent), color(false)
			{}

			binary_node(__value_type *_content, __node_type &_left, __node_type &_right) : 
				_value(_content),  left(&_left), right(&_right), color(false)
			{}
			
			~binary_node(){};

	}; // class binary_node

	template <class T>
	std::ostream &operator<<(std::ostream &out, binary_node<T> &node)
	{
		if (node.color)
			out<< BWHITE;
		else
			out<< BRED;
		out <<"(";
		out << node.parent;
		out << ")(";
		out << node.left <<"|" << node.right;
		out << ")";
		out <<"[" << node.value() <<"]";
		out << COLOR_OFF;
		return (out);
	}

	template <class T>
	bool operator==(const binary_node<T>& x, const binary_node<T>& y)
	{
		return (x.value() == y.value());
	}

	template <class T>
	bool operator!=(const binary_node<T>& x, const binary_node<T>& y)
	{
		return (!(x == y));
	}

	template <class T>
	bool operator< (const binary_node<T>& x, const binary_node<T>& y)
	{
		return (x.value() < y.value());
	}

	template <class T>
	bool operator> (const binary_node<T>& x, const binary_node<T>& y)
	{
		return (y < x);
	}

	template <class T>
	bool operator>=(const binary_node<T>& x, const binary_node<T>& y)
	{
		return (!(x < y));
	}

	template <class T>
	bool operator<=(const binary_node<T>& x, const binary_node<T>& y)
	{
		return (!(y < x));
	}
}; // namespace ft

#endif