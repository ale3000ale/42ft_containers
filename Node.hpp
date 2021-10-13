/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:11:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/10/13 19:07:21 by amarcell         ###   ########.fr       */
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

			__value_type						value;
			__node_type_pointer					left;
			__node_type_pointer					right;
			__node_type_pointer         		parent;
			bool								is_black;

			void __set_parent(__node_type_pointer _p)
			{
				parent = _p;
			}

		public:
			binary_node(): 
				value(), left(nullptr), right(nullptr), parent(nullptr), is_black(false)
			{}

			binary_node(__value_type _content) : 
				value(_content), left(nullptr), right(nullptr), parent(nullptr), is_black(false)
			{}

			binary_node(__node_type_pointer _parent): parent(_parent), is_black(false)
			{
			}

			binary_node(__value_type _content, __node_type &_parent) : 
				value(_content), parent(&_parent), is_black(false)
			{}

			binary_node(__value_type _content, __node_type &_parent, __node_type &_left, __node_type &_right) : 
				value(_content), left(&_left), right(&_right), parent(&_parent), is_black(false)
			{}

			binary_node(__value_type _content, __node_type &_left, __node_type &_right) : 
				value(_content),  left(&_left), right(&_right), is_black(false)
			{}
			

			binary_node(__node_type const &node)
			{
				*this = node;
			}
			
			binary_node& operator=(binary_node const& nd)
			{
				if (this != &nd)
				{
					left = nd.left;
					right = nd.right;
					parent = nd.parent;
					value = nd.value;
					is_black = nd.is_black;
				}
				return *this;
			}
			~binary_node(){};
	};

	template <class T>
	std::ostream &operator<<(std::ostream &out, binary_node<T> &node)
	{
		if (node.is_black)
			out<< BWHITE;
		else
			out<< BRED;
		out <<"(";
		out << node.parent;
		out << ")(";
		out << node.left <<"|" << node.right;
		out << ")";
		out <<"[" << node.value <<"]";
		out << COLOR_OFF;
		return (out);
	}
};

#endif