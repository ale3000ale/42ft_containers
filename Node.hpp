/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:11:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/10/06 18:32:33 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_H__
# define NODE_H__

# include "utils.hpp"
# include <memory> // for std::allocator


namespace ft
{
	template <class _Tp>
	class binary_node
	{
		public:

			typedef class binary_node<_Tp>			__node_type;
			typedef class binary_node<_Tp>*			__node_type_pointer;
			typedef _Tp								__value_type;

			__value_type						content;
			__node_type_pointer					left;
			__node_type_pointer					right;
			__node_type_pointer         		parent;

			void __set_parent(__node_type &_p)
			{
				parent = &_p;
			}

		public:
			binary_node()
			{}

			binary_node(__value_type _content) : 
				content(_content), left(nullptr), right(nullptr), parent(nullptr)
			{}

			binary_node(__node_type_pointer _parent)
			{
				parent = _parent;
			}

			binary_node(__value_type _content, __node_type &_parent) : 
				content(_content), parent(&_parent)
			{}

			binary_node(__value_type _content, __node_type &_parent, __node_type &_left, __node_type &_right) : 
				content(_content), left(&_left), right(&_right), parent(&_parent)
			{}

			binary_node(__value_type _content, __node_type &_left, __node_type &_right) : 
				content(_content),  left(&_left), right(&_right)
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
					content = nd.content;
				}
				return *this;
			}
			~binary_node(){};
	};

	template <class T>
	std::ostream &operator<<(std::ostream &out, binary_node<T> &node)
	{
		out <<"(";
		out << node.parent;
		out << ")(";
		out << node.left <<"|" << node.right;
		out << ")";
		out <<"[" << node.content <<"]";
		return (out);
	}
};

#endif