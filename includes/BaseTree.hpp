#ifndef BASETREE_H__
# define BASETREE_H__

# include "Node.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include "TreeIterator.hpp"
# include <memory> // for std::allocator

namespace ft
{
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
			x = x->parent;
		return (x->parent);
	}

	template <class NodePtr>
	NodePtr tree_prev_node(NodePtr x)
	{
		if (x->left != nullptr)
			return (tree_max(x->left));
		while (tree_is_left_child(x))
			x = x->parent;
		return (x->parent);
	}

	template <	class _Tp,
				class _Compare, 
				class _Allocator = std::allocator<_Tp> >
	class base_tree
	{
		# define BLACK true
		# define RED false
		public:
			typedef _Tp                                     	value_type;
			typedef _Compare                                 	value_compare;
			typedef _Allocator                               	value_allocator;

			typedef binary_node<value_type>						__node;
			typedef binary_node<value_type>*					__node_pointer;
			typedef __node_pointer								__parent_pointer;
			typedef __node_pointer								__iter_pointer;
			typedef typename value_allocator::template rebind<__node>::other node_allocator;
			typedef typename node_allocator::difference_type	difference_type;
			typedef typename node_allocator::size_type       	size_type;

			typedef tree_iterator<value_type, difference_type>			iterator;
			typedef tree_const_iterator<value_type, difference_type>	const_iterator;

		private:
			
			node_allocator				node_alloc;
			value_compare				cmp;
			__node_pointer				root_pointer;
			__node_pointer				end_leaf_pointer;
			size_type					_size;
			value_allocator				value_alloc;

		public:

			base_tree(): _size(0)
			{
			};

			explicit base_tree(const value_compare& __comp): 
				cmp(__comp),root_pointer(nullptr), end_leaf_pointer(create_node(root_pointer)), _size(0)
			{
			};
			explicit base_tree(const value_allocator& __a): 
				value_alloc(__a),root_pointer(nullptr), end_leaf_pointer(create_node(root_pointer)), _size(0)
			{
			};
			base_tree(const value_compare& __comp, const value_allocator& __a): 
				cmp(__comp), value_alloc(__a), root_pointer(nullptr), end_leaf_pointer(create_node(root_pointer)), _size(0)
			{
			};
			base_tree(const base_tree& __t, const value_allocator& __a = value_allocator()) : root_pointer(nullptr)
			{
				value_alloc = __a;
				*this = __t;
			};
			
			base_tree& operator=(const base_tree& __t)
			{
				if (this != &__t)
				{
					clear_all();
					node_alloc = __t.node_alloc;
					value_alloc = __t.value_alloc;
					cmp = __t.cmp;

					root_pointer = copy_tree(__t.end_leaf_pointer, __t.root_pointer);
					_size =__t.size();
				}
				return (*this);
			};

			void swap(base_tree& other)
			{
				std::swap(this->root_pointer, other.root_pointer);
				std::swap(this->end_leaf_pointer, other.end_leaf_pointer);
				std::swap(this->node_alloc, other.node_alloc);
				std::swap(this->value_alloc, other.value_alloc);
				std::swap(this->_size, other._size);
				std::swap(this->cmp, other.cmp);
			};

		private:
			__node_pointer copy_tree(const __node_pointer end, const __node_pointer cp, __node_pointer parent = nullptr)
			{
				__node_pointer n;
				if (cp != end)
					n = (parent) ?
						create_node(cp->value(), parent)
					:
						create_node(cp->value());
				else
					n = create_node(parent);

				n->color = cp->color;
				if (cp->left != nullptr)
					n->left = copy_tree(end, cp->left, n);
				if (cp->right != nullptr)
					n->right = copy_tree(end, cp->right, n);
				if (cp == end)
					end_leaf_pointer = n;
				return (n);
			}

		public:

			~base_tree() 
			{
				clear_all();
				destroy_node(end_leaf_pointer);
			};

			iterator begin()
				{
					if (_size == 0)
						return (iterator(end_leaf_pointer));
					return (iterator(find_first(root_pointer))); 
				};
			const_iterator begin() const
				{
					if (_size == 0)
						return (const_iterator(end_leaf_pointer));
					return (const_iterator(find_first(root_pointer)));
				};
			iterator end()
				{ return (iterator(end_leaf_pointer)); };
			const_iterator end() const
				{ return (const_iterator(end_leaf_pointer)); };

			size_type size() const
				{return _size;}

			size_type max_size() const
			{
				return (node_alloc.max_size());
			};

			node_allocator & _node_allocator() const
				{ return (node_alloc); };
			value_allocator & _value_allocator() const
				{ return (value_alloc); };
			const value_compare & _value_compare() const
				{ return (cmp); };


			/*-------------------------------NODE----------------------------*/

			__node_pointer create_node(value_type value)
			{
				__node_pointer node = node_alloc.allocate(1);
				value_type *new_value = value_alloc.allocate(1);
				value_alloc.construct(new_value, value);
				_size++;
				node_alloc.construct(node, new_value);
				return (node);
			}

			__node_pointer create_node( __node_pointer parent)
			{
				__node_pointer node = create_node(value_type());
				node->__set_parent(parent);
				return (node);
			}

			__node_pointer create_node(value_type value, __node_pointer &parent)
			{
				__node_pointer node = create_node(value);
				if (cmp(value, parent->value()))
					parent->left = node;
				else
					parent->right = node;

				node->parent = parent;
				return (node);
			}

			void destroy_node(__node_pointer &n)
			{
				if (!n)
					return ;
				if (n == end_leaf_pointer->parent)
					end_leaf_pointer->parent = n->parent;
				if (n != end_leaf_pointer)
					_size--;
				value_alloc.destroy(n->_value);
				value_alloc.deallocate(n->_value, 1);
				node_alloc.destroy(n);
				node_alloc.deallocate(n, 1);
				n = nullptr;
			}

			iterator find(const value_type value)		const
			{
				__node_pointer node = root_pointer;
				while (node != nullptr)
				{
					if (!cmp(value, node->value()) && !cmp(node->value(), value))
						return (iterator(node));
					else if (cmp(value, node->value()))	//default    node->_value < value
						node = node->left;
					else
						node = node->right;
				}
				return (iterator(end_leaf_pointer));
			}

			size_type count(const value_type& value) const
			{
				if (find(value) == end())
					return (0);
				return (1);
			}

		private:
			__node_pointer find(const value_type value, __node_pointer &parent) const
			{
				__node_pointer node = root_pointer;
				parent = node;
				while (node != nullptr)
				{
					if (!cmp(value, node->value()) && !cmp(node->value(), value)) // value == node->_value
						return (node);
					else if (cmp(value, node->value()))	//default    node->_value < value
					{
						parent = node;
						node = node->left;
					}
					else
					{
						parent = node;
						node = node->right;
					}
				}
				return (node);
			}

		public:
			__node_pointer find_last(__node_pointer n)
			{
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

			__node_pointer find_first(__node_pointer n) const
			{
				
				if (n == nullptr || n->left == nullptr )
					return n;
				__node_pointer tmp = n->left;
				while (tmp->left != nullptr)
					tmp = tmp->left;
				return tmp;
			}
			__node_pointer find_first()	const
			{
				return find_first(root_pointer);
			}


			iterator lower_bound(const value_type& value)
			{
				__node_pointer root = root_pointer;
				__node_pointer result = end_leaf_pointer;
				while (root)
				{ 
					if (!(cmp(root->value(), value))) // value >= k
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}

			iterator lower_bound(const value_type& value, __node_pointer root)
			{
				__node_pointer result = end_leaf_pointer;
				while (root)
				{ 
					if (!(cmp(root->value(), value))) // value >= k
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}
			const_iterator lower_bound(const value_type& value) const
			{
				__node_pointer root = root_pointer;
				__node_pointer result = end_leaf_pointer;
				while (root)
				{ 
					if (!(cmp(root->value(), value))) // value >= k
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return const_iterator(result);
			}


			iterator upper_bound(const value_type& value)
			{
				__node_pointer root = root_pointer;
				__node_pointer result = end_leaf_pointer;
				while (root)
				{
					if (cmp(value, root->value())) // k < value
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}

			iterator upper_bound(const value_type& value, __node_pointer root)
			{
				__node_pointer result = end_leaf_pointer;
				while (root)
				{
					if (cmp(value, root->value())) // k < value
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return iterator(result);
			}
			const_iterator upper_bound(const value_type& value) const
			{
				__node_pointer root = root_pointer;
				__node_pointer result = end_leaf_pointer;
				while (root)
				{
					if (cmp(value, root->value())) // k < value
					{
						result = root;
						root = root->left;
					}
					else
						root = root->right;
				}
				return const_iterator(result);
			}


			pair<iterator,iterator> equal_range(const value_type& value)
			{ return (pair<iterator,iterator>(lower_bound(value), upper_bound(value))); };

			pair<const_iterator,const_iterator> equal_range(const value_type& value) const
			{ return (pair<const_iterator,const_iterator>(lower_bound(value), upper_bound(value))); };


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


			void rotate_left(__node_pointer n)
			{
				__node_pointer supp = n->right->left;
				n->right->parent = n->parent;
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
				if (n->parent == nullptr)
					n->color = BLACK;
				else
					insert_case2(n);
			}

			void insert_case2(__node_pointer n) 
			{
				if (n->parent->color == BLACK)
					return; 
				else
					insert_case3(n);
			}

			void insert_case3(__node_pointer n)
			{
				if (uncle(n) != NULL && uncle(n)->color == RED) {
					n->parent->color = BLACK;
					uncle(n)->color = BLACK;
					grandparent(n)->color = RED;
					insert_case1(n->parent->parent);
				}
				else
					insert_case4(n);
			}

			void insert_case4(__node_pointer n)
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

			void insert_case5(__node_pointer n)
			{
				n->parent->color = BLACK;
				grandparent(n)->color = RED;
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
			ft::pair<iterator, bool> insert(value_type value)
			{
				__node_pointer node, parent;
				if (root_pointer == nullptr)
				{
					root_pointer = create_node(value);
					root_pointer->color = true;
					node = root_pointer;
					end_leaf_pointer->parent = root_pointer;
				}
				else
				{
					end_leaf_pointer->parent->right = nullptr;
					node = find(value , parent);
					if (node == nullptr)
					{
						node = create_node(value, parent);
						//balancer
						insert_case1(node);
					}
					else
					{
						end_leaf_pointer->parent->right = end_leaf_pointer;
						return (ft::pair<iterator, bool>(iterator(node), false));
					}
				}
				if (end_leaf_pointer->parent->right == node)
				{
					node->right = end_leaf_pointer;
					end_leaf_pointer->parent = node;
				}
				else
					end_leaf_pointer->parent->right = end_leaf_pointer;
				return (ft::pair<iterator, bool>(iterator(node), true));
			}


			
			/*------------------------NODE DELETE------------------------*/

		private:

			void replace_node(__node_pointer n, __node_pointer child)
			{
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
	
				if (n->parent == NULL)
					return;
				else
					delete_case2(n);
			}

			void delete_case2(__node_pointer n)
			{
				if (sibling(n) && sibling(n)->color == RED) 
				{
					n->parent->color = RED;
					sibling(n)->color = BLACK;
					if (n == n->parent->left)
						rotate_left(n->parent);
					else
						rotate_right(n->parent);
				}
				delete_case3(n);
			}

			 void delete_case3(__node_pointer n)
			 {
				 if (!sibling(n))
					return;
				if (n->parent->color == BLACK &&
					sibling(n)->color == BLACK &&
					(sibling(n)->left == nullptr || sibling(n)->left->color == BLACK) &&
					(sibling(n)->right == nullptr || sibling(n)->right->color == BLACK))
				{
					sibling(n)->color = RED;
					delete_case1(n->parent);
				}
				else
					delete_case4(n);
			}

			void delete_case4(__node_pointer n)
			{
				if (n->parent->color == RED &&
					sibling(n)->color == BLACK &&
					(sibling(n)->left == nullptr || sibling(n)->left->color == BLACK) &&
					(sibling(n)->right == nullptr || sibling(n)->right->color == BLACK))
				{
					sibling(n)->color = RED;
					n->parent->color = BLACK;
				}
				else
					delete_case5(n);
			}

			void delete_case5(__node_pointer n) 
			{
				if (n == n->parent->left &&
					sibling(n)->color == BLACK &&
					(sibling(n)->left == nullptr || sibling(n)->left->color == RED) &&
					(sibling(n)->right == nullptr || sibling(n)->right->color == BLACK))
				{
					sibling(n)->color = RED;
					sibling(n)->left->color = BLACK;
					rotate_right(sibling(n));
				}
				else if (n == n->parent->right &&
						sibling(n)->color == BLACK &&
						(sibling(n)->right == nullptr || sibling(n)->right->color == RED) &&
						(sibling(n)->left == nullptr || sibling(n)->left->color == BLACK))
				{
					sibling(n)->color = RED;
					sibling(n)->right->color = BLACK;
					rotate_left(sibling(n));
				}
				delete_case6(n);
			}

			void delete_case6(__node_pointer n) 
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

			iterator erase(__node_pointer n)
			{
				iterator it(n);
				++it;
				

				if (_size == 1)
				{
					destroy_node(n);
					root_pointer = nullptr;
					end_leaf_pointer->parent = nullptr;
					return (it);
				}
				else if (n == end_leaf_pointer->parent)
				{
					n->right = nullptr;
					end_leaf_pointer->parent = (n->parent) ? n->parent : n->left;
				}
				if (end_leaf_pointer->parent)
					end_leaf_pointer->parent->right = nullptr;
				
				if (n->left != nullptr && n->right != nullptr)
				{
					// children > 1
					//std::cout << "delete double child" << *n << std::endl;
					__node_pointer tmp = find_last(n->left);
					std::swap<value_type*>(tmp->_value, n->_value);
					erase(tmp);
					return (it);
				}
				
				//std::cout << *it._ptr << std::endl;
				/* Assuming n has at most one non-null child */
				//std::cout << "delete: " << *n << std::endl;
				__node_pointer child = (n->left == nullptr) ? n->right: n->left;
				if (child == nullptr)
					delete_case1(n);
				replace_node(n, child);
				
				if (n->color == BLACK && child != nullptr) 
				{
					if (child->color == RED)
						child->color = BLACK;
					else
						delete_case1(child);
				}
				end_leaf_pointer->parent->right = end_leaf_pointer;
				destroy_node(n);
				return (it);
			}

			iterator erase(const_iterator n)
			{
				return erase(n._ptr);
			}

			iterator erase(const_iterator first, const_iterator last)
			{
				iterator ret(first._ptr);
				
				while (ret != last)
					ret = erase(ret._ptr);
				return (ret);
			}

			size_type erase(const value_type& k)
			{
				iterator i = find(k);
				if (i != end())
				{
					erase(i);
					return (1);
				}
				return (0);
			};

		private:
			void destroy_all(__node_pointer &n)
			{
				if (n != nullptr && n != end_leaf_pointer)
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

	}; // class base_tree
}; // namespace ft

# endif