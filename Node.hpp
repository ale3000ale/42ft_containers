/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:11:39 by amarcell          #+#    #+#             */
/*   Updated: 2021/10/04 18:52:03 by amarcell         ###   ########.fr       */
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

			typedef binary_node<_Tp>                      		  				__node_type;
			typedef *__node_type                                      	        __node_type_pointer;

			typedef __node_type    	__node_type_pointer;
			typedef _Tp				__value_type;

			__value_type			content;
			__node_type				left;
			__node_type				right;
			__node_type         	parent;

			void __set_parent(pointer _p)
			{
				parent = p;
			}

		private:
			binary_node() : 
				left(nullptr), right(nullptr), parent(nullptr), content()
			{}

			binary_node(__value_type _content) : 
				content(_content), left(nullptr), right(nullptr), parent(nullptr)
			{}

			binary_node(__value_type _content, __node_type _parent) : 
				content(_content), parent(_parent), left(nullptr), right(nullptr)
			{}

			binary_node(__value_type _content, __node_type _parent, __node_type _left, __node_type _right) : 
				content(_content), parent(_parent), left(_left), right(_right)
			{}

			binary_node(__value_type _content, __node_type _left, __node_type _right) : 
				content(_content),  left(_left), right(_right), parent(nullptr)
			{}
			
			binary_node(binary_node const& nd)
			{
				*this = nd;
			}

			binary_node& operator=(binary_node const& nd);
			{
				left = nd.left;
				right = nd.right;
				parent = nd.parent;
				content = nd.content;
			}
			~binary_node();
	};
};

#endif