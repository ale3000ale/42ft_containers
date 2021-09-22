

#ifndef ITERATOR_H__
#define ITERATOR_H__

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

namespace ft
{
	// define the traits of iterator from an iterator
	template<class Iterator>
		struct iterator_traits
		{
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
		};

	// define the traits of iterator from a Class
	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};
};



#endif