#ifndef BASETREE_H__
# define BASETREE_H__

# include "Node.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include <memory> // for std::allocator
# include <__tree>

namespace ft
{
	# define BLACK true
	# define RED false

	//TODO: sostituire il bynary node con il tree_node
	template <class _Tp, class _Compare, class _Allocator>
	class base_tree
	{
		public:
			/*------------------*/
			typedef _Tp                                     	value_type;
			typedef _Compare                                 	value_compare;
			typedef _Allocator                               	allocator_type;
			typedef typename value_type::first_type				key_type;
								/*FALSE=black TRUE=red*/
			typedef binary_node<value_type>						__node;
			typedef binary_node<value_type>*					__node_pointer;
			typedef __node_pointer								__parent_pointer;
			typedef __node_pointer								__iter_pointer;
			typedef std::allocator<__node>						allocator_node;

		public:
			
			
			allocator_node				alloc;
			value_type					value;
			value_compare				cmp;
			__node_pointer				root_pointer;
			__node_pointer				end_leaf_pointer;
			size_t						size;

		public:

			explicit base_tree(const value_compare& __comp): cmp(__comp),root_pointer(nullptr), size(0)
			{
			};

			explicit base_tree(const allocator_type& __a): alloc(__a),root_pointer(nullptr), size(0)
			{
			};

			base_tree(const value_compare& __comp, const allocator_type& __a): cmp(__comp), alloc(__a), root_pointer(nullptr), size(0)
			{
			};

			base_tree(const base_tree& __t)
			{
				*this = __t;
			};

			/* base_tree& operator=(const base_tree& __t)
			{
				if (this != &__t)
					//TODO: copy tree;
				return (*this);
			}; */

			~base_tree(){};

			__node_pointer create_node(value_type value)
			{
				__node_pointer node = alloc.allocate(1);
				size++;
				alloc.construct(node);
				node->value = value;
				return (node);
			}

			__node_pointer create_node(value_type value, __node_pointer &parent)
			{
				__node_pointer node = create_node(value);
				if (cmp(value.first, parent->value.first))
						parent->left = node;
					else
						parent->right = node;

				node->parent = parent;
				return (node);
			}

			void destroy_node(__node_pointer &n)
			{
				__node_pointer p = n->parent;
				alloc.destroy(n);
				alloc.deallocate(&n, 1);
				
				if (p != nullptr)
				{
					if (n == p->left)
						n->parent->left = nullptr;
					else
						n->parent->right = nullptr;
				}
				n = nullptr;
				size--;
			}

			__node_pointer find_node(key_type value)
			{
				__node_pointer node = *root_pointer;
				while (node != nullptr)
				{
					if (value == node->value)
						return (node);
					else if (ccmp(value, node->value.first))	//default    node->value < value
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}

			__node_pointer find_node(key_type value, __node_pointer &parent)
			{
				__node_pointer node = root_pointer;
				parent = node;
				while (node != nullptr)
				{
					if (value == node->value.first)
						return (node);
					else if (cmp(value, node->value.first))	//default    node->value < value
					{
						std::cout << "inside find left: " << std::endl;
						parent = node;
						node = node->left;
					}
					else
					{
						std::cout << "inside find rigth: " << std::endl;
						parent = node;
						node = node->right;
					}
				}
				return (node);
			}

			/*------------------------TREE NODE MANAGMENT------------------------*/
		private:

			__node_pointer grandparent( __node_pointer &n)
			{
				if (n->parent == nullptr)
					return (nullptr);
				return n->parent->parent;
			}

			__node_pointer uncle( __node_pointer &n)
			{
				if (n->parent == grandparent(n)->left)
					return grandparent(n)->right;
				else
					return grandparent(n)->left;
			}

			__node_pointer sibling( __node_pointer &n)
			{
				if (n == n->parent->left)
					return n->parent->right;
				else
					return n->parent->left;
			}

			bool is_leaf(__node_pointer n)
			{
				return (n->left == nullptr &&
						n->right == nullptr &&
						n->parent != nullptr);
			}


			void rotate_left(__node_pointer &n)
			{
				__node_pointer supp = n->right->left;
				n->right->parent = n->parent;
				if (n->parent != nullptr)
				{
					((n->parent->left == n) ? n->parent->left : n->parent->right) = n->right;
					n->right->parent = n->parent;
				}
				else
					root_pointer = n->right;
				n->right->left = n;
				n->parent = n->right;
				n->right = supp; 
				supp->parent = n;
			}

			void rotate_right(__node_pointer &n)
			{
				__node_pointer supp = n->left->right;
				n->left->parent = n->parent;
				if (n->parent != nullptr)
				{
					((n->parent->left == n) ? n->parent->left : n->parent->right) = n->left;
					n->left->parent = n->parent;
				}
				else
					root_pointer = n->left;
				n->left->right = n;
				n->parent = n->left;
				n->left = supp; 
				supp->parent = n;
			}


			/*------------------------NODE INSERT------------------------*/
		
			

			void insert_case1(__node_pointer &n)		//insert in root
			{
				if (n->parent == nullptr)
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
					insert_case1(n->parent->parent);
				}
				else
					insert_case4(n);
			}

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
					rotate_right(n->parent->parent);
				} else {
					/* Here, n == n->parent->right && n->parent == grandparent(n)->right */
					rotate_left(n->parent->parent);
				}
			}
		public:
			__node_pointer insert(value_type value)
			{
				__node_pointer node, parent;
				//std::cout << "insert: " << root_pointer << std::endl;
				if (root_pointer == nullptr)
				{
					root_pointer = create_node(value);
					root_pointer->is_black = true;
					//std::cout << "root \n"; 
					return (root_pointer);
				}
				
				node = find_node(value.first , parent);
				std::cout << "find: " << parent << std::endl;
				if (node == nullptr)
					node = create_node(value, parent);
				else
					node->value = value;
				//balancer
				insert_case1(node);
				return (node);
			}
			
			/*------------------------NODE DELETE------------------------*/
		private:
			void replace_node(__node_pointer &n, __node_pointer &child)
			{
				child->left = n->left;
				child->right = n->right;
				if ( n->parent != nullptr)
					child->parent = n->parent;
				else
				{
					root_pointer = child;
					child->parent = nullptr;	
				}		
			}

			void delete_case1(__node_pointer &n)
			{
				if (n->parent == NULL)
					return;
				else
					delete_case2(n);
			}

			void delete_case2(__node_pointer &n)
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

			 void delete_case3(__node_pointer &n)
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

			void delete_case4(__node_pointer &n) 
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

			 void delete_case5(__node_pointer &n) 
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

			void delete_case6(__node_pointer &n) 
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

			void delete_node(__node_pointer &n)
			{
				/* Si assume che n ha al massimo un figlio non nullo */
				__node_pointer child = (is_leaf(n->right)) ? n->left: n->right;	
				replace_node(n, child);
				if (n->is_black == BLACK) 
				{
					if (child->is_black == RED)
						child->is_black = BLACK;
					else
						delete_case1(child);
				}
				destroy_node(n);
			}

			void clear_all(__node_pointer &n)
			{
				if (n->right != nullptr)
					clear_all(n->right);
				if (n->left != nullptr)
					clear_all(n->left);
				delete_node(n);
			}
	};
};

# endif