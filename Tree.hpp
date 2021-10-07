/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:36:23 by amarcell          #+#    #+#             */
/*   Updated: 2021/10/07 02:04:41 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H__
# define TREE_H__

# include "Node.hpp"
# include "utils.hpp"
# include "pair.hpp"
# include <memory> // for std::allocator
# include <__tree>

namespace ft
{
	//TODO: sostituire il bynary node con il tree_node
	template <class _Tp, class _Compare, class _Allocator>
	class tree
	{
		public:
			/*------------------*/
			typedef typename _Tp                                     	value_type;
			typedef	typename _Compare                                 	value_compare;
			typedef typename _Allocator                               	allocator_type;
								/*FALSE=black TRUE=red*/
			typedef binary_node<pair<bool, value_type>					__node;
			typedef typename __node*									__node_pointer;
			typedef typename __node_pointer								__parent_pointer;
			typedef typename __node_pointer								__iter_pointer;

		private:
			
			
			allocator_type				alloc;
			value_type					content;
			value_compare				cmp;
			__node_pointer				root_pointer;
			__node_pointer				end_leaf_pointer;
			
			/*------------------*/

			typedef allocator_traits<allocator_type>         __alloc_traits;
			typedef typename __make_tree_node_types<value_type,
					typename __alloc_traits::void_pointer>::type
															_NodeTypes;
			typedef typename _NodeTypes::key_type           key_type;
		public:
			typedef typename _NodeTypes::__node_value_type      __node_value_type;
			typedef typename _NodeTypes::__container_value_type __container_value_type;

			typedef typename __alloc_traits::pointer         pointer;
			typedef typename __alloc_traits::const_pointer   const_pointer;
			typedef typename __alloc_traits::size_type       size_type;
			typedef typename __alloc_traits::difference_type difference_type;

		public:
			typedef typename _NodeTypes::__void_pointer        __void_pointer;

			//typedef typename _NodeTypes::__node_type           __node;
			//typedef typename _NodeTypes::__node_pointer        __node_pointer;

			typedef typename _NodeTypes::__node_base_type      __node_base;
			//typedef typename _NodeTypes::__node_base_pointer   __node_base_pointer;

			typedef typename _NodeTypes::__end_node_type       __end_node_t;
			typedef typename _NodeTypes::__end_node_pointer    __end_node_ptr;

			//typedef typename _NodeTypes::__parent_pointer      __parent_pointer;
			//typedef typename _NodeTypes::__iter_pointer        __iter_pointer;

			typedef typename __rebind_alloc_helper<__alloc_traits, __node>::type __node_allocator;
			typedef allocator_traits<__node_allocator>         __node_traits;

		public:
			__iter_pointer __end_node()
			{
				return (end_leaf_pointer);
			}
		
			__iter_pointer __end_node() const
			{
				return const_cast<__iter_pointer&>(end_leaf_pointer);
			}
			
			__node_allocator& __node_alloc()  
			{
				return (alloc());
			}
		private:
			
			const 	__node_allocator& 	__node_alloc() const 
			{
				return (alloc());
			}
			
			__iter_pointer& 	__begin_node()
			{
				return(root_pointer);
			}
			
			const 	__iter_pointer&	__begin_node() const  
			{
				 return const_cast<__iter_pointer&>(root_pointer);
			}
		public:
			
			allocator_type 	__alloc() const 
			{
				return allocator_type(__node_alloc());
			}
		private:
			//TODO: non lo so
			//size_type& 	size()  {}
		public:
			//TODO: non lo so
			//const size_type& size() const  {}
			
			value_compare& value_comp()
			{
				return (cmp);
			}
			
			const value_compare& value_comp() const 
			{
				return (cmp);
			}
		public:

			__node __root() const 
			{
				return *root_pointer;
			}

			__node_pointer __root_ptr() const  
			{
				return root_pointer
			}
			
			typedef __tree_iterator<value_type, __node_pointer, difference_type>             iterator;
			typedef __tree_const_iterator<value_type, __node_pointer, difference_type> const_iterator;

			/*----------------------------------CONSTRUCTUR----------------------------------*/
			explicit tree(const value_compare& __comp): cmp(__comp)
			{
				__begin_node() = __end_node();
			};

			explicit tree(const allocator_type& __a): alloc(__a)
			{
				__begin_node() = __end_node()
			};

			tree(const value_compare& __comp, const allocator_type& __a): cmp(__comp), alloc(__a)
			{
				__begin_node() = __end_node()
			};

			tree(const tree& __t)
			{
				*this = __t;
			};

			tree& operator=(const tree& __t)
			{
				if (this != &__t)
			};

			~tree();

			
			template <class _InputIterator>
			void __assign_unique(_InputIterator __first, _InputIterator __last);

			template <class _InputIterator>
			void __assign_multi(_InputIterator __first, _InputIterator __last);

			

			//TODO: vedere l'iteratore cosa chiede
			iterator begin()   
			{
				return       iterator(__begin_node());
			}
			
			const_iterator begin() const  {return const_iterator(__begin_node());}
			
			iterator end()  {return       iterator(__end_node());}
			
			const_iterator end() const  {return const_iterator(__end_node());}

			
			size_type max_size() const
			{return std::min<size_type>(
										__node_traits::max_size(__node_alloc()),
										numeric_limits<difference_type >::max());}

			void clear() ;

			void swap(tree& __t)

			template <class _Key, class _Args>
			
			pair<iterator, bool> __emplace_unique_key_args(_Key const&, _Args& __args);
			template <class _Key, class _Args>
			
			iterator __emplace_hint_unique_key_args(const_iterator, _Key const&, _Args&);
			
			pair<iterator, bool> __insert_unique(const __container_value_type& __v) {
				return __emplace_unique_key_args(_NodeTypes::__get_key(__v), __v);
			}

			iterator __insert_unique(const_iterator __p, const __container_value_type& __v) {
				return __emplace_hint_unique_key_args(__p, _NodeTypes::__get_key(__v), __v);
			}

			iterator __insert_multi(const __container_value_type& __v);
			
			iterator __insert_multi(const_iterator __p, const __container_value_type& __v);

			pair<iterator, bool> __node_insert_unique(__node_pointer __nd);
			
			iterator             __node_insert_unique(const_iterator __p,
													__node_pointer __nd);

			iterator __node_insert_multi(__node_pointer __nd);
			
			iterator __node_insert_multi(const_iterator __p, __node_pointer __nd);

			 iterator
			__remove_node_pointer(__node_pointer) ;

			iterator erase(const_iterator __p);
			iterator erase(const_iterator __f, const_iterator __l);
			template <class _Key>
				size_type __erase_unique(const _Key& __k);
			template <class _Key>
				size_type __erase_multi(const _Key& __k);

			void __insert_node_at(__parent_pointer     __parent,
								__node_base_pointer& __child,
								__node_base_pointer __new_node) ;

			template <class _Key>
				iterator find(const _Key& __v);
			template <class _Key>
				const_iterator find(const _Key& __v) const;

			template <class _Key>
				size_type __count_unique(const _Key& __k) const;
			template <class _Key>
				size_type __count_multi(const _Key& __k) const;

			template <class _Key>
				
				iterator lower_bound(const _Key& __v)
					{return __lower_bound(__v, __root(), __end_node());}
			template <class _Key>
				iterator __lower_bound(const _Key& __v,
									__node_pointer __root,
									__iter_pointer __result);
			template <class _Key>
				
				const_iterator lower_bound(const _Key& __v) const
					{return __lower_bound(__v, __root(), __end_node());}
			template <class _Key>
				const_iterator __lower_bound(const _Key& __v,
											__node_pointer __root,
											__iter_pointer __result) const;
			template <class _Key>
				
				iterator upper_bound(const _Key& __v)
					{return __upper_bound(__v, __root(), __end_node());}
			template <class _Key>
				iterator __upper_bound(const _Key& __v,
									__node_pointer __root,
									__iter_pointer __result);
			template <class _Key>
				
				const_iterator upper_bound(const _Key& __v) const
					{return __upper_bound(__v, __root(), __end_node());}
			template <class _Key>
				const_iterator __upper_bound(const _Key& __v,
											__node_pointer __root,
											__iter_pointer __result) const;
			template <class _Key>
				pair<iterator, iterator>
				__equal_range_unique(const _Key& __k);
			template <class _Key>
				pair<const_iterator, const_iterator>
				__equal_range_unique(const _Key& __k) const;

			template <class _Key>
				pair<iterator, iterator>
				__equal_range_multi(const _Key& __k);
			template <class _Key>
				pair<const_iterator, const_iterator>
				__equal_range_multi(const _Key& __k) const;

			typedef __tree_node_destructor<__node_allocator> _Dp;
			typedef unique_ptr<__node, _Dp> __node_holder;

			__node_holder remove(const_iterator __p) ;
		private:
			__node_base_pointer&
				__find_leaf_low(__parent_pointer& __parent, const key_type& __v);
			__node_base_pointer&
				__find_leaf_high(__parent_pointer& __parent, const key_type& __v);
			__node_base_pointer&
				__find_leaf(const_iterator __hint,
							__parent_pointer& __parent, const key_type& __v);
			// FIXME: Make this function const qualified. Unfortunetly doing so
			// breaks existing code which uses non-const callable comparators.
			template <class _Key>
			__node_base_pointer&
				__find_equal(__parent_pointer& __parent, const _Key& __v);
			template <class _Key>
			 __node_base_pointer&
			__find_equal(__parent_pointer& __parent, const _Key& __v) const {
			return const_cast<tree*>(this)->__find_equal(__parent, __v);
			}
			template <class _Key>
			__node_base_pointer&
				__find_equal(const_iterator __hint, __parent_pointer& __parent,
							__node_base_pointer& __dummy,
							const _Key& __v);

			__node_holder __construct_node(const __container_value_type& __v);

			void destroy(__node_pointer __nd) ;

			
			void __copy_assign_alloc(const tree& __t)
				{__copy_assign_alloc(__t, integral_constant<bool,
					__node_traits::propagate_on_container_copy_assignment::value>());}

			
			void __copy_assign_alloc(const tree& __t, true_type)
				{
				if (__node_alloc() != __t.__node_alloc())
					clear();
				__node_alloc() = __t.__node_alloc();
				}
			
			void __copy_assign_alloc(const tree&, false_type) {}

			void __move_assign(tree& __t, false_type);
			void __move_assign(tree& __t, true_type)
				_(is_nothrow_move_assignable<value_compare>::value &&
						is_nothrow_move_assignable<__node_allocator>::value);

			
			void __move_assign_alloc(tree& __t)
				_(
					!__node_traits::propagate_on_container_move_assignment::value ||
					is_nothrow_move_assignable<__node_allocator>::value)
				{__move_assign_alloc(__t, integral_constant<bool,
					__node_traits::propagate_on_container_move_assignment::value>());}

			
			void __move_assign_alloc(tree& __t, true_type)
				_(is_nothrow_move_assignable<__node_allocator>::value)
				{__node_alloc() = _VSTD::move(__t.__node_alloc());}
			
			void __move_assign_alloc(tree&, false_type)  {}

			__node_pointer __detach();
			static __node_pointer __detach(__node_pointer);

			template <class, class, class, class> friend class _LIBCPP_TEMPLATE_VIS map;
	};
};

#endif