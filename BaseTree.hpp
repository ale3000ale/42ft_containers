#ifndef BASETREE_H__
# define BASETREE_H__

# include "Node.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include <memory> // for std::allocator
# include <__tree>

namespace ft
{
	# define BLACK true;
	# define RED false;

	//TODO: sostituire il bynary node con il tree_node
	template <class _Tp, class _Compare, class _Allocator>
	class base_tree
	{
		public:
			/*------------------*/
			typedef typename _Tp                                     	value_type;
			typedef	typename _Compare                                 	value_compare;
			typedef typename _Allocator                               	allocator_type;
								/*FALSE=black TRUE=red*/
			typedef binary_node<value_type>						__node;
			typedef binary_node<value_type>*						__node_pointer;
			typedef typename __node_pointer								__parent_pointer;
			typedef typename __node_pointer								__iter_pointer;

		private:
			
			
			allocator_type				alloc;
			value_type					content;
			value_compare				cmp;
			__node_pointer				root_pointer;
			__node_pointer				end_leaf_pointer;
			size_t						size;

		public:

			explicit base_tree(const value_compare& __comp): cmp(__comp), size(0)
			{
				__begin_node() = __end_node();
			};

			explicit base_tree(const allocator_type& __a): alloc(__a), size(0)
			{
				__begin_node() = __end_node()
			};

			base_tree(const value_compare& __comp, const allocator_type& __a): cmp(__comp), alloc(__a), size(0)
			{
				__begin_node() = __end_node()
			};

			base_tree(const tree& __t)
			{
				*this = __t;
			};

			base_tree& operator=(const base_tree& __t)
			{
				if (this != &__t)
			};

			~base_tree();

			__node_pointer create_node(value_type value)
			{
				__node_pointer node = alloc.allocate(1);
				size++;
				alloc.construct(&node, value);
				return (node);
			}

			__node_pointer create_node(value_type value, __node_pointer &parent)
			{
				__node_pointer node = create_node(value);
				if (cmd(value, parent->content))
						parent->left = node;
					else
						parent->right = node;
				if (!parent->is_black)
					node->is_black = true;
				node->parent = parent;
				return (node);
			}

			__node_pointer find_node(value_type value)
			{
				__node_pointer node = *root_pointer;
				while (node != nullptr)
				{
					if (value == node->content)
						return (node);
					else if (cmp(node->content , value))	//default    node->content < value
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}

			__node_pointer find_node(value_type value, __node_pointer &parent)
			{
				__node_pointer node = *root_pointer;
				parent = node;
				while (node != nullptr)
				{
					if (value == node->content)
						return (node);
					else if (cmp(node->content , value))	//default    node->content < value
					{
						node = node->left;
						if (node != nullptr)
							parent = node->parent;
					}
					else
					{
						node = node->right;
						if (node != nullptr)
							parent = node->parent;
					}
				}
				return (node);
			}

			/*------------------------TREE NODE MANAGMENT------------------------*/
			__node_pointer grandparent(const __node_pointer &n) const
			{
				return n->parent->parent;
			}

			__node_pointer uncle(const __node_pointer &n) const
			{
				if (n->parent == grandparent(n)->left)
					return grandparent(n)->right;
				else
					return grandparent(n)->left;
			}

			__node_pointer sibling(const __node_pointer &n) const
			{
				if (n == n->parent->left)
					return n->parent->right;
				else
					return n->parent->left;
			}

			/*------------------------NODE INSERT------------------------*/
		private:
			void insert_case1(__node_pointer &n)		//insert in root
			{
				if (n->parent == NULL)
					n->is_black = BLACK;
				else
					insert_case2(n);
			}

			void insert_case2(__node_pointer &n) 
			{
				if (n->parent->is_black == BLACK)
					return; 
				else
					insert_case3(n);
			}

			void insert_case3(__node_pointer &n)
			{
				if (uncle(n) != NULL && uncle(n)->is_black == RED) {
					n->parent->is_black = BLACK;
					uncle(n)->is_black = BLACK;
					grandparent(n)->is_black = RED;
					insert_case1(grandparent(n));
				}
				else
					insert_case4(n);
			}

			//TODO: __node_pointer rotate_left(__node_pointer n);
			//TODO: __node_pointer rotate_rigth(__node_pointer n);
			void insert_case4(__node_pointer &n)
			{
				if (n == n->parent->right && n->parent == grandparent(n)->left) {
					rotate_left(n->parent);
					n = n->left;
				} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
					rotate_right(n->parent);
					n = n->right;
				}
					insert_case5(n);
			}

			void insert_case5(__node_pointer &n)
			{
				n->parent->is_black = BLACK;
				grandparent(n)->is_black = RED;
				if (n == n->parent->left && n->parent == grandparent(n)->left) {
					rotate_right(grandparent(n));
				} else {
					/* Here, n == n->parent->right && n->parent == grandparent(n)->right */
					rotate_left(grandparent(n));
				}
			}
		public:
			__node_pointer insert(value_type value)
			{
				__node_pointer node, parent;

				if (root_pointer == nullptr)
				{
					root_pointer = create_node(value);
					root_pointer->is_black = true;
					return (root_pointer);
				}
				node = find_node(value, parent);
				if (node == nullptr)
					node = create_node(value, parent);
				else
					node->content = value;
				insert_case1(node);
				return (node);
			}
			/*------------------------NODE DELETE------------------------*/
		private:
			void delete_case1(node n)
			{
				if (n->parent == NULL)
					return;
				else
					delete_case2(n);
			}

			void delete_case2(node n)
			{
				if (sibling(n)->is_black == RED) {
					n->parent->is_black = RED;
					sibling(n)->is_black = BLACK;
					if (n == n->parent->left)
						rotate_left(n->parent);
					else
						rotate_right(n->parent);
				}
				delete_case3(n);
			}

			 void delete_case3(node n)
			 {
				if (n->parent->color == BLACK &&
					sibling(n)->color == BLACK &&
					sibling(n)->left->color == BLACK &&
					sibling(n)->right->color == BLACK)
				{
					sibling(n)->color = RED;
					delete_case1(n->parent);
				}
				else
					delete_case4(n);
			}

			void delete_case4(node n) 
			{
				if (n->parent->color == RED &&
					sibling(n)->color == BLACK &&
					sibling(n)->left->color == BLACK &&
					sibling(n)->right->color == BLACK)
				{
					sibling(n)->color = RED;
					n->parent->color = BLACK;
				}
				else
					delete_case5(n);
			}

			 void delete_case5(node n) 
			 {
				if (n == n->parent->left &&
					sibling(n)->color == BLACK &&
					sibling(n)->left->color == RED &&
					sibling(n)->right->color == BLACK)
				{
					sibling(n)->color = RED;
					sibling(n)->left->color = BLACK;
					rotate_right(sibling(n));
				}
				else if (n == n->parent->right &&
						sibling(n)->color == BLACK &&
						sibling(n)->right->color == RED &&
						sibling(n)->left->color == BLACK)
				{
					sibling(n)->color = RED;
					sibling(n)->right->color = BLACK;
					rotate_left(sibling(n));
				}
				delete_case6(n);
			}

			void delete_case6(node n) 
			{
				sibling(n)->color = n->parent->color;
				n->parent->color = BLACK;
				if (n == n->parent->left) {
					/* Here, sibling(n)->right->color == RED */
					sibling(n)->right->color = BLACK;
					rotate_left(n->parent);
				}
				else
				{
					/* Here, sibling(n)->left->color == RED */
					sibling(n)->left->color = BLACK;
					rotate_right(n->parent);
				}
			}
		public:
			void delete_one_child(__node_pointer n) 
			{
				/* Si assume che n ha al massimo un figlio non nullo */
				//TODO: bool is_leaf(__node_pointer n;
				__node_pointer child = (is_leaf(n->right)) ? n->left: n->right;	
				//TODO:  __node_pointer replace_node(__node_pointer n, __node_pointer child);
				replace_node(n, child);
				if (n->is_black == BLACK) {
					if (child->is_black == RED)
						child->is_black = BLACK;
					else
						delete_case1(child);
				}
				free(n);
			}
	};
};

# endif