#ifndef BASETREE_H__
# define BASETREE_H__

# include "Node.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include "MapIterator.hpp"
# include <memory> // for std::allocator
# include <limits>

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

	//TODO: sostituire il bynary node con il tree_node
	template <	class _Tp,
				class _Compare, 
				class _Allocator = std::allocator<binary_node<_Tp> > >
	class base_tree
	{
		public:
			typedef _Tp                                     	value_type;
			typedef _Compare                                 	value_compare;
			typedef _Allocator                               	allocator_type;

			typedef binary_node<value_type>						__node;
			typedef binary_node<value_type>*					__node_pointer;
			typedef __node_pointer								__parent_pointer;
			typedef __node_pointer								__iter_pointer;
			typedef std::allocator<__node>						allocator_node;
			typedef typename allocator_node::difference_type	difference_type;
			typedef typename allocator_node::size_type       	size_type;

			typedef tree_iterator<value_type, difference_type>			iterator;
			typedef tree_const_iterator<value_type, difference_type>	const_iterator;

		private:
			
			allocator_node				alloc;
			value_compare				cmp;
			__node_pointer				root_pointer;
			__node_pointer				end_leaf_pointer;
			size_type					_size;
			allocator_type				alloc_type;

		public:

			base_tree(): _size(0)
			{
			};

			explicit base_tree(const value_compare& __comp): 
				cmp(__comp),root_pointer(nullptr), end_leaf_pointer(create_node(root_pointer)), _size(0)
			{
			};

			explicit base_tree(const allocator_type& __a): 
				alloc_type(__a),root_pointer(nullptr), end_leaf_pointer(create_node(root_pointer)), _size(0)
			{
			};

			base_tree(const value_compare& __comp, const allocator_type& __a): 
				cmp(__comp), alloc_type(__a), root_pointer(nullptr), end_leaf_pointer(create_node(root_pointer)), _size(0)
			{
			};
			

			base_tree(const base_tree& __t, const allocator_type& __a = allocator_type())
			{
				alloc_type = __a;
				*this = __t;
				
			};
			

			base_tree& operator=(const base_tree& __t)
			{
				if (this != &__t)
				{
					clear_all();
					alloc = __t.alloc;
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
				std::swap(this->alloc, other.alloc);
				std::swap(this->alloc_type, other.alloc_type);
				std::swap(this->_size, other._size);
				std::swap(this->cmp, other.cmp);
			};

		private:
			__node_pointer copy_tree(const __node_pointer end, const __node_pointer cp, __node_pointer parent = nullptr)
			{
				__node_pointer n;
				if (cp != end)
					n = (parent) ?
						create_node(cp->_value, parent)
					:
						create_node(cp->_value);
				else
					n = create_node(parent);

				n->is_black = cp->is_black;
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
				return (alloc_type.max_size());
			};

			allocator_node & _node_allocator() const
				{ return (alloc); };
			allocator_type & _value_allocator() const
				{ return (alloc_type); };
			const value_compare & _value_compare() const
				{ return (cmp); };


			/*-------------------------------NODE----------------------------*/

			__node_pointer create_node(value_type value)
			{
				__node_pointer node = alloc.allocate(1);
				_size++;
				alloc.construct(node, value);
				return (node);
			}

			__node_pointer create_node( __node_pointer parent)
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
				//std::cout << "parent: " << *parent << "\nMe: " << *node << std::endl ;
				return (node);
			}

			void destroy_node(__node_pointer &n)
			{
				if (!n)
					return ;
				if (/*n != nullptr && */n == end_leaf_pointer->parent)
					end_leaf_pointer->parent = n->parent;
				if (n != end_leaf_pointer)
					_size--;
				alloc.destroy(n);
				alloc.deallocate(n, 1);
				n = nullptr;
				
			}

			iterator find(const value_type value)		const
			{
				__node_pointer node = root_pointer;
				//value_type k(key);
				////std::cout << "inside find KEY" << std::endl;
				while (node != nullptr)
				{
					if (!cmp(value, node->_value) && !cmp(node->_value, value))
						return (iterator(node));
					else if (cmp(value, node->_value))	//default    node->_value < value
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
			/*__node_pointer __find(const key_type& key) const
			{
				__node_pointer node = root_pointer;
				while (node != nullptr)
				{
					if (key == node->_value.first)
						return (node);
					else if (cmp(key, node->_value.first))	//default    node->_value < value
						node = node->left;
					else
						node = node->right;
				}
				return (end_leaf_pointer);
			}*/

			__node_pointer find(const value_type value, __node_pointer &parent) const
			{
				__node_pointer node = root_pointer;
				parent = node;
				while (node != nullptr)
				{
					if (!cmp(value, node->_value) && !cmp(node->_value, value)) // value == node->_value
						return (node);
					else if (cmp(value, node->_value))	//default    node->_value < value
					{
						////std::cout << "inside find left: " << std::endl;
						parent = node;
						node = node->left;
					}
					else
					{
						////std::cout << "inside find rigth: " << std::endl;
						parent = node;
						node = node->right;
					}
				}
				return (node);
			}

		public:
			__node_pointer find_last(__node_pointer n)
			{
				////std::cout << "last " << std::endl;
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
					if (!(cmp(root->_value, value))) // value >= k
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
					if (!(cmp(root->_value, value))) // value >= k
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
					if (!(cmp(root->_value, value))) // value >= k
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
					if (cmp(value, root->_value)) // k < value
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
					if (cmp(value, root->_value)) // k < value
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
					if (cmp(value, root->_value)) // k < value
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
				//std::cout << "leaf? " << std::endl;
				return (n->left == nullptr &&
						n->right == nullptr &&
						n->parent != nullptr);
			}


			void rotate_left(__node_pointer n)
			{
				//std::cout << "rotate left " << *n <<std::endl;
				
				__node_pointer supp = n->right->left;
				n->right->parent = n->parent;
				////std::cout << "SUPP: CORRECT "<< *n << " \n";
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
				//std::cout << "rotate rigth: " << *n <<std::endl;
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
				//std::cout << "insert case 1\n"; 
				if (n->parent == nullptr)
					n->is_black = BLACK;
				else
					insert_case2(n);
			}

			void insert_case2(__node_pointer n) 
			{
				//std::cout << "insert case 2\n"; 
				if (n->parent->is_black == BLACK)
					return; 
				else
					insert_case3(n);
			}

			void insert_case3(__node_pointer n)
			{
				//std::cout << "insert case 3\n";
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
				//std::cout << "insert case 4\n"; 
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
				//std::cout << "insert case 5\n";
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
			ft::pair<iterator, bool> insert(value_type value)
			{
				__node_pointer node, parent;
				//std::cout << value << std::endl;
				////std::cout << "insert: " << root_pointer << std::endl;
				if (root_pointer == nullptr)
				{
					root_pointer = create_node(value);
					root_pointer->is_black = true;
					////std::cout << "root \n"; 
					node = root_pointer;
					end_leaf_pointer->parent = root_pointer;
				}
				else
				{
					end_leaf_pointer->parent->right = nullptr;
					node = find(value , parent);
					////std::cout << "find: " << parent << std::endl;
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
				//std::cout << "replace: " << n << " -> " << child << std::endl;
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
				//std::cout << "delete 1  " << *n << std::endl;
				if (n->parent == NULL)
					return;
				else
					delete_case2(n);
			}

			void delete_case2(__node_pointer n)
			{
				//std::cout << "delete 2\n";
				if (sibling(n) && sibling(n)->is_black == RED) 
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
				 //std::cout << "delete 3\n";
				 if (!sibling(n))
					return;
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
				//std::cout << "delete 4\n";
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
				// std::cout << "delete 5\n";
				if (n == n->parent->left &&
					sibling(n)->is_black == BLACK &&
					(sibling(n)->left == nullptr || sibling(n)->left->is_black == RED) &&
					(sibling(n)->right == nullptr || sibling(n)->right->is_black == BLACK))
				{
					sibling(n)->is_black = RED;
					sibling(n)->left->is_black = BLACK;
					rotate_right(sibling(n));
				}
				else if (n == n->parent->right &&
						sibling(n)->is_black == BLACK &&
						(sibling(n)->right == nullptr || sibling(n)->right->is_black == RED) &&
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
				//std::cout << "delete 6\n";
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

			iterator erase(__node_pointer n)
			{
				iterator it(n);
				++it;
				

				if (_size == 1)
				{
					//std::cout << n << " AOOOOOO\n";
					destroy_node(n);
					root_pointer = nullptr;
					end_leaf_pointer->parent = nullptr;
					return (it);
				}
				else if (n == end_leaf_pointer->parent)
				{
					//std::cout << *n << " AOOOOOO2\n";
					n->right = nullptr;
					end_leaf_pointer->parent = (n->parent) ? n->parent : n->left;
				}
				if (end_leaf_pointer->parent)
					end_leaf_pointer->parent->right = nullptr;
				
				if (n->left != nullptr && n->right != nullptr)
				{
					// childrens > 1
					//std::cout << "delete double child" << *n << std::endl;
					__node_pointer tmp = find_last(n->left);
					std::swap<value_type>(tmp->_value, n->_value);
					erase(tmp);
					return (it);
				}
				
				//std::cout << *it._ptr << std::endl;
				/* Si assume che n ha al massimo un figlio non nullo */
				//std::cout << "delete: " << *n << std::endl;
				__node_pointer child = (n->left == nullptr) ? n->right: n->left;
				if (child == nullptr)
					delete_case1(n);
				replace_node(n, child);
				
				//std::cout << "AO CLEAR FATHER" << std::endl;
				if (n->is_black == BLACK && child != nullptr) 
				{
					//std::cout << "AO " << std::endl;
					if (child->is_black == RED)
						child->is_black = BLACK;
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
				{
					//std::cout << *ret._ptr << " == "<< *last._ptr << std::endl;
					ret = erase(ret._ptr);

					//std::cout << *ret._ptr << " == "<< *last._ptr << std::endl;
					//std::cout << *((++ret2)._ptr) << " == "<< *last._ptr << std::endl;
				}
				
				return (ret);

					// ----------PRIMA--------

				/* const_iterator actual = first;
				const_iterator next = ++first; */ 
				//std::cout << *actual._ptr << "  "<< *next._ptr << "  " << *last._ptr << std::endl;
				/* while (actual != last)
				{
					erase(actual);
					actual = next;
					next = ++next;
				} */
				//return erase(actual);
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

	};
};

# endif