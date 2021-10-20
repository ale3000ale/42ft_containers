#ifndef BASETREE_H__
# define BASETREE_H__

# include "Node.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include "MapIterator.hpp"
# include <memory> // for std::allocator

namespace ft
{
	# define BLACK true
	# define RED false

	template <class NodePtr>
	bool tree_is_left_child(NodePtr x)
	{
		return (x == x->parent->left);
	}

	// Returns:  pointer to the left-most node under x.
	template <class NodePtr>
	NodePtr tree_min(NodePtr x)
	{
		while (x->left != nullptr)
			x = x->left;
		return (x);
	}

	// Returns:  pointer to the right-most node under x.
	template <class NodePtr> 
	NodePtr tree_max(NodePtr x)
	{
		while (x->right != nullptr)
			x = x->right;
		return (x);
	}

	template <class NodePtr>
	NodePtr tree_next_node(NodePtr x)
	{
		if (x->right != nullptr)
			return (tree_min(x->right));
		while (!tree_is_left_child(x))
			x = x->parent();
		return (x->parent());
	}

	template <class NodePtr>
	NodePtr tree_prev_node(NodePtr x)
	{
		if (x->_left != nullptr)
			return (tree_max(x->left));
		while (tree_is_left_child(x))
			x = x->parent();
		return (x->parent());
	}

	//TODO: sostituire il bynary node con il tree_node
	template <	class _Tp,
				class _Compare = ft::less<_Tp> , 
				class _Allocator = std::allocator<binary_node<_Tp> > >
	class base_tree
	{
		public:
			typedef _Tp                                     	value_type;
			typedef _Compare                                 	value_compare;
			typedef _Allocator                               	allocator_type;
			typedef typename value_type::first_type				key_type;

			typedef binary_node<value_type>						__node;
			typedef binary_node<value_type>*					__node_pointer;
			typedef __node_pointer								__parent_pointer;
			typedef __node_pointer								__iter_pointer;
			typedef std::allocator<__node>						allocator_node;
			typedef typename allocator_node::difference_type	difference_type;
			typedef typename allocator_node::size_type       	size_type;

			typedef tree_iterator<value_type, difference_type>			iterator;
			typedef tree_const_iterator<value_type, difference_type>	const_iterator;

		public:
			
			
			allocator_node				alloc;
			value_compare				cmp;
			__node_pointer				root_pointer;
			__node_pointer				end_leaf_pointer;
			size_type					_size;

		public:

			base_tree(): _size(0)
			{
			};

			//TODO: chek constructur
			explicit base_tree(const value_compare& __comp): 
				cmp(__comp),root_pointer(nullptr), end_leaf_pointer(nullptr), _size(0)
			{
			};

			explicit base_tree(const allocator_type& __a): 
				alloc(__a),root_pointer(nullptr), end_leaf_pointer(nullptr), _size(0)
			{
			};

			base_tree(const value_compare& __comp, const allocator_type& __a): 
				cmp(__comp), alloc(__a), root_pointer(nullptr), end_leaf_pointer(nullptr), _size(0)
			{
			};

			base_tree(const base_tree& __t, const allocator_type& __a)
			{
				*this = __t;
				alloc = __a;
			};
			

			base_tree& operator=(const base_tree& __t)
			{
				if (this != &__t)
				{
					clear_all();
					alloc = __t.alloc;
					cmp = __t.cmp;

					root_pointer = copy_tree(__t.root_pointer);
					end_leaf_pointer = create_node(find_last(root_pointer));
				}
				return (*this);
			};
		private:
			__node_pointer copy_tree(const __node_pointer cp)
			{
				__node_pointer n = create_node(cp->_value);
				n->is_black = cp->is_black;
				if (cp->left != nullptr)
					n->left = copy_tree(cp->left);
				if (cp->right != nullptr)
					n->right = copy_tree(cp->right);
				return (n);
				
			}

		public:

			~base_tree() 
			{
				clear_all();
				destroy_node(end_leaf_pointer);
			};



			iterator begin()
				{ return (iterator(root_pointer)); };
			const_iterator begin() const
				{ return (const_iterator(root_pointer)); };
			iterator end()
				{ return (iterator(end_leaf_pointer)); };
			const_iterator end() const
				{ return (const_iterator(end_leaf_pointer)); };

			size_type size()
				{return _size;}


			/*-------------------------------NODE----------------------------*/

			__node_pointer create_node(value_type value)
			{
				__node_pointer node = alloc.allocate(1);
				_size++;
				alloc.construct(node);
				node->_value = value;
				return (node);
			}

			__node_pointer create_node( __node_pointer &parent)
			{
				__node_pointer node = alloc.allocate(1);
				alloc.construct(node);
				node->__set_parent(parent);
				return (node);
			}

			__node_pointer create_node(value_type value, __node_pointer &parent)
			{
				__node_pointer node = create_node(value);
				if (cmp(value, parent->_value))
						parent->left = node;
					else
						parent->right = node;

				node->parent = parent;
				return (node);
			}

			void destroy_node(__node_pointer &n)
			{
				if (n != nullptr && n == end_leaf_pointer->parent)
					end_leaf_pointer->parent = n->parent;
				alloc.destroy(n);
				alloc.deallocate(n, 1);
				n = nullptr;
				_size--;
			}

			iterator find(const key_type key)		const
			{
				__node_pointer node = root_pointer;
				value_type k;
				k.first = key;
				std::cout << "inside find" << std::endl;
				while (node != nullptr)
				{
					if (key == node->_value.first)
						return (iterator(node));
					else if (cmp(k, node->_value))	//default    node->_value < value
						node = node->left;
					else
						node = node->right;
				}
				return (iterator(end_leaf_pointer));
			}

			size_type count(const key_type& k)
			{
				if (find(k) == end_leaf_pointer)
					return (0);
				return (1);
			}

		private:
			__node_pointer find(const value_type value) const
			{
				__node_pointer node = root_pointer;
				std::cout << "inside find" << std::endl;
				while (node != nullptr)
				{
					if (value == node->_value)
						return (node);
					else if (cmp(value, node->_value))	//default    node->_value < value
						node = node->left;
					else
						node = node->right;
				}
				return (node);
			}

			__node_pointer find(const value_type value, __node_pointer &parent) const
			{
				__node_pointer node = root_pointer;
				parent = node;
				while (node != nullptr)
				{
					if (value == node->_value)
						return (node);
					else if (cmp(value, node->_value))	//default    node->_value < value
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

		public:
			__node_pointer find_last(__node_pointer n)
			{
				std::cout << "last " << std::endl;
				if (n->right == nullptr)
					return n;
				__node_pointer tmp = n->right;
				while (tmp->right != nullptr)
					tmp = tmp->right;
				return tmp;
			}

			__node_pointer find_last()
			{
				return find_last(root_pointer);
			}

			__node_pointer find_first(__node_pointer n)
			{
				std::cout << "first " << std::endl;
				if (n->left == nullptr)
					return n;
				__node_pointer tmp = n->left;
				while (tmp->left != nullptr)
					tmp = tmp->left;
				return tmp;
			}
			__node_pointer find_first()
			{
				return find_first(root_pointer);
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
				std::cout << "leaf? " << std::endl;
				return (n->left == nullptr &&
						n->right == nullptr &&
						n->parent != nullptr);
			}


			void rotate_left(__node_pointer n)
			{
				std::cout << "rotate left " << *n <<std::endl;
				
				__node_pointer supp = n->right->left;
				n->right->parent = n->parent;
				//std::cout << "SUPP: CORRECT "<< *n << " \n";
				if (n->parent != nullptr)
				{
					((n->parent->left == n) ? n->parent->left : n->parent->right) = n->right;
					n->right->parent = n->parent;
				}
				else
				{
					root_pointer = n->right;
				}
				n->right->left = n;
				n->parent = n->right;
				n->right = supp; 
				if (supp != nullptr)
					supp->parent = n;
			}

			void rotate_right(__node_pointer n)
			{
				std::cout << "rotate rigth: " << *n <<std::endl;
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
				if (supp != nullptr)
					supp->parent = n;
			}


			/*------------------------NODE INSERT------------------------*/
		
			

			void insert_case1(__node_pointer n)		//insert in root
			{
				std::cout << "insert case 1\n"; 
				if (n->parent == nullptr)
					n->is_black = BLACK;
				else
					insert_case2(n);
			}

			void insert_case2(__node_pointer n) 
			{
				std::cout << "insert case 2\n"; 
				if (n->parent->is_black == BLACK)
					return; 
				else
					insert_case3(n);
			}

			void insert_case3(__node_pointer n)
			{
				std::cout << "insert case 3\n";
				if (uncle(n) != NULL && uncle(n)->is_black == RED) {
					n->parent->is_black = BLACK;
					uncle(n)->is_black = BLACK;
					grandparent(n)->is_black = RED;
					insert_case1(n->parent->parent);
				}
				else
					insert_case4(n);
			}

			void insert_case4(__node_pointer n)
			{
				std::cout << "insert case 4\n"; 
				if (n == n->parent->right && n->parent == grandparent(n)->left) {
					rotate_left(n->parent);
					n = n->left;
				} else if (n == n->parent->left && n->parent == grandparent(n)->right) {
					rotate_right(n->parent);
					n = n->right;
				}
				insert_case5(n);
			}

			void insert_case5(__node_pointer n)
			{
				std::cout << "insert case 5\n";
				n->parent->is_black = BLACK;
				grandparent(n)->is_black = RED;
				if (n == n->parent->left && n->parent == grandparent(n)->left) 
				{
					rotate_right(n->parent->parent);
				}
				else 
				{	
					rotate_left(n->parent->parent);
				}
			}
		public:
			iterator insert(value_type value)
			{
				__node_pointer node, parent;
				//std::cout << "insert: " << root_pointer << std::endl;
				if (root_pointer == nullptr)
				{
					root_pointer = create_node(value);
					root_pointer->is_black = true;
					//std::cout << "root \n"; 
					node = root_pointer;
					end_leaf_pointer = create_node(root_pointer);
				}
				else
				{
					node = find(value , parent);
					//std::cout << "find: " << parent << std::endl;
					if (node == nullptr)
					{
						node = create_node(value, parent);
						//balancer
						insert_case1(node);
					}
					else
						node->_value = value;
				}
				if (end_leaf_pointer->parent->right == node)
					end_leaf_pointer->parent = node;
				return (iterator(node));
			}
			
			/*------------------------NODE DELETE------------------------*/

		private:
			void replace_node(__node_pointer n, __node_pointer child)
			{
				std::cout << "replace: " << n << " -> " << child << std::endl;
				if (child != nullptr)
				{
					if (child != n->left)
						child->left = n->left;
					if (child != n->right)
						child->right = n->right;
					if ( n->parent != nullptr)
					{
						child->parent = n->parent;
						if (n->parent->left == n)
							n->parent->left = child;
						else
							n->parent->right = child;
					}
					else
					{
						root_pointer = child;
						child->parent = nullptr;	
					}
				}
				else
				{
					if (n->parent->left == n)
						n->parent->left = nullptr;
					else
						n->parent->right = nullptr;
				}
			}

			void delete_case1(__node_pointer n)
			{
				std::cout << "delete 1\n";
				if (n->parent == NULL)
					return;
				else
					delete_case2(n);
			}

			void delete_case2(__node_pointer n)
			{
				std::cout << "delete 2\n";
				if (sibling(n)->is_black == RED) 
				{
					n->parent->is_black = RED;
					sibling(n)->is_black = BLACK;
					if (n == n->parent->left)
						rotate_left(n->parent);
					else
						rotate_right(n->parent);
				}
				delete_case3(n);
			}

			 void delete_case3(__node_pointer n)
			 {
				 std::cout << "delete 3\n";
				if (n->parent->is_black == BLACK &&
					sibling(n)->is_black == BLACK &&
					(sibling(n)->left == nullptr || sibling(n)->left->is_black == BLACK) &&
					(sibling(n)->right == nullptr || sibling(n)->right->is_black == BLACK))
				{
					sibling(n)->is_black = RED;
					delete_case1(n->parent);
				}
				else
					delete_case4(n);
			}

			void delete_case4(__node_pointer n)
			{
				std::cout << "delete 4\n";
				if (n->parent->is_black == RED &&
					sibling(n)->is_black == BLACK &&
					(sibling(n)->left == nullptr || sibling(n)->left->is_black == BLACK) &&
					(sibling(n)->right == nullptr || sibling(n)->right->is_black == BLACK))
				{
					sibling(n)->is_black = RED;
					n->parent->is_black = BLACK;
				}
				else
					delete_case5(n);
			}

			 void delete_case5(__node_pointer n) 
			 {
				 std::cout << "delete 5\n";
				if (n == n->parent->left &&
					sibling(n)->is_black == BLACK &&
					(sibling(n)->left != nullptr && sibling(n)->left->is_black == RED) &&
					(sibling(n)->right == nullptr || sibling(n)->right->is_black == BLACK))
				{
					sibling(n)->is_black = RED;
					sibling(n)->left->is_black = BLACK;
					rotate_right(sibling(n));
				}
				else if (n == n->parent->right &&
						sibling(n)->is_black == BLACK &&
						(sibling(n)->right != nullptr && sibling(n)->right->is_black == RED) &&
						(sibling(n)->left == nullptr || sibling(n)->left->is_black == BLACK))
				{
					sibling(n)->is_black = RED;
					sibling(n)->right->is_black = BLACK;
					rotate_left(sibling(n));
				}
				delete_case6(n);
			}

			void delete_case6(__node_pointer n) 
			{
				std::cout << "delete 6\n";
				sibling(n)->is_black = n->parent->is_black;
				n->parent->is_black = BLACK;
				if (n == n->parent->left) {
					/* Here, sibling(n)->right->is_black == RED */
					sibling(n)->right->is_black = BLACK;
					rotate_left(n->parent);
				}
				else
				{
					/* Here, sibling(n)->left->is_black == RED */
					sibling(n)->left->is_black = BLACK;
					rotate_right(n->parent);
				}
			}
		public:

			void erase(__node_pointer n)
			{
				if (root_pointer != nullptr && n == end_leaf_pointer->parent)
					end_leaf_pointer->parent = n->parent;
				__node_pointer tmp;
				if (n->left != nullptr && n->right != nullptr)
				{
					// childrens > 1
					std::cout << "delete double child" << *n << std::endl;
					tmp = find_last(n->left);
					ft::swap<value_type>(tmp->_value, n->_value);
					erase(tmp);
					return;
				}

				/* Si assume che n ha al massimo un figlio non nullo */
				std::cout << "delete: " << *n << std::endl;
				__node_pointer child = (n->left == nullptr) ? n->right: n->left;
				if (n->is_black == BLACK )
					delete_case1(n);
				replace_node(n, child);
				std::cout << "AO CLEAR FATHER" << std::endl;
				if (n->is_black == BLACK && child != nullptr) 
				{

					std::cout << "AO " << std::endl;
					if (child->is_black == RED)
						child->is_black = BLACK;
					else
						delete_case1(child);
				}
				destroy_node(n);
			}

			void erase(const_iterator n)
			{
				erase(n._ptr);
			}

			/* void erase()
			{
				__node_pointer node = *n;
				__node_pointer parent = node->parent;
				bool left = (node->parent->left == node) ?
										true : false;
				while (node == nullptr)
					erase(node);

				if (left)
					parent->left = nullptr;
				else
					parent->right = nullptr;
			} */

		private:
			void destroy_all(__node_pointer &n)
			{
				if (n != nullptr)
				{
					if (n->right != nullptr)
						destroy_all(n->right);
					if (n->left != nullptr)
						destroy_all(n->left);
					destroy_node(n); 
				}
			}
		public:
			void clear_all()
			{
				destroy_all(root_pointer);
			}
	};
};

# endif