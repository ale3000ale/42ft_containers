
#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <limits>
# include "VectorIterator.hpp"


# include <vector>

std::vector<int> test;
namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
			typedef T                                        value_type;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef VectorIterator<pointer>                  iterator;
			typedef VectorIterator<const_pointer>            const_iterator;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;
			// sistemare il nome del reverse iterator
			typedef reverse_iterator<iterator>          	reverse_iterator;
			typedef reverse_iterator<const_iterator>    	const_reverse_iterator;

			vector(const allocator_type& alloc = allocator_type()) : _array(nullptr), _size(0), _capacity(0), _alloc(alloc){}
			explicit vector(size_type n, const allocator_type& alloc = allocator_type()) : _array(nullptr), _size(0), _capacity(0), _alloc(alloc)
			{
				reserve(n);
			};
			vector(size_type n, const value_type& value, const allocator_type& = allocator_type()) : _array(nullptr), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(n, value);
			};
			template <class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type()) : _array(nullptr), _size(0), _capacity(0), _alloc(alloc)
				{
					assign(first, last);
				};
			vector(const vector& x)
			{
				*this = other;
			};
			~vector()
			{
				if (_array != nullptr)
				{
					clear();
					// da sistemare
					__alloc_traits::deallocate(__alloc(), _array, _capacity);
				}
			};
			vector& operator=(const vector& x)
			{
				assign(x.begin(), x.end());
			};

			/* assign function */
			template <class InputIterator>
				void assign(InputIterator first, InputIterator last)
				{
					clear();
					insert(begin(), first, last);				
				};
			void assign(size_type n, const value_type& u)
			{
				clear();
				insert(begin(), n, u);
			};

			allocator_type get_allocator() const
			{
				allocator_type copy(_alloc);
				return (copy);	
			};

			/* iterators funcs */
			iterator               begin()
			{
				return (iterator(_array));
			};
			const_iterator         begin()		const
			{
				return (const_iterator(_array));
			};
			iterator               end()
			{
				return (iterator(&_array[_size]));
			};
			const_iterator         end()		const
			{
				return (const_iterator(&_array[_size]));
			};
			reverse_iterator       rbegin()
			{
				return (reverse_iterator(end()));
			};
			const_reverse_iterator rbegin()		const
			{
				return (const_reverse_iterator(end()));
			};
			reverse_iterator       rend()
			{
				return (reverse_iterator(begin()));
			};
			const_reverse_iterator rend()		const
			{
				return (const_reverse_iterator(begin()));
			};

			const_iterator         cbegin()		const
			{
				return(begin());
			};
			const_iterator         cend()		const
			{
				return(end());
			};
			const_reverse_iterator crbegin()	const
			{
				return(rbegin());
			};
			const_reverse_iterator crend()		const
			{
				return (rend());
			};

			size_type size() const
			{
				return (_size);
			};
			size_type max_size() const
			{
				// return (unsigned long long max value / sizeof(T)
				//return (ULLONG_MAX / sizeof(value_type));
				return (_alloc.max_size());
			};
			size_type capacity() const
			{
				return (_capacity);
			};
			bool empty()
			{
				return (_size == 0);
			};
			void reserve(size_type n)
			{
				if (_capacity >= n)
					return ;
				// creare un nuovo vettore, copiarlo e liberare quello vecchio
			};
			void shrink_to_fit()
			{
				if (!(_capacity > _size))
					return ;
				// creare un nuovo vettore, copiarlo e liberare quello vecchio
			};

			// non faccio mezzo controllo sulla correttezza dell'indice richiesto, non sicuro
			reference       operator[](size_type n)
			{
				return (_array[n]);
			};
			const_reference operator[](size_type n) const
			{
				return (_array[n]);
			};
			reference       at(size_type n)
			{
				return (_array[n]);
			};
			const_reference at(size_type n) const
			{
				return (_array[n]);
			};

			value_type*       data()
			{
				return (_array);
			};
			const value_type* data() const
			{
				return (_array);
			};

			reference       front()
			{
				return (*_array);
			};
			const_reference front() const
			{
				return (*_array);
			};
			reference       back()
			{
				return (_array[_size - 1]);
			};
			const_reference back() const
			{
				return (_array[_size - 1]);
			};

			void push_back(const value_type& x);
			void pop_back();

			iterator insert(const_iterator position, const_reference x);
			iterator insert(const_iterator position, size_type n, const value_type& x);
			template <class InputIterator>
				iterator insert(const_iterator position, InputIterator first, InputIterator last);

			iterator erase(const_iterator position);
			iterator erase(const_iterator first, const_iterator last);

			void clear();

			void resize(size_type sz);
			void resize(size_type sz, const value_type& c);

			void swap(vector&);

		private:
			pointer			_array;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			
	};

	/* non-member funcs */
	template <class T> bool operator==(const vector<T>& x, const vector<T>& y);
	template <class T> bool operator< (const vector<T>& x, const vector<T>& y);
	template <class T> bool operator!=(const vector<T>& x, const vector<T>& y);
	template <class T> bool operator> (const vector<T>& x, const vector<T>& y);
	template <class T> bool operator>=(const vector<T>& x, const vector<T>& y);
	template <class T> bool operator<=(const vector<T>& x, const vector<T>& y);
};

#endif