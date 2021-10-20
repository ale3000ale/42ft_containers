
#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory> // for std::allocator
# include "VectorIterator.hpp"
# include "utils.hpp"

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
			typedef ft::reverse_iterator<iterator>          	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>    	const_reverse_iterator;

			vector(const allocator_type& alloc = allocator_type()) : _array(nullptr), _size(0), _capacity(0), _alloc(alloc){}
			vector(size_type n, const_reference value = value_type(), const allocator_type& alloc = allocator_type()) : _array(nullptr), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(n, value);
			};
			template <class InputIterator>
				vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator >::type* = 0)
					: _array(nullptr), _size(0), _capacity(0), _alloc(alloc)
				{
					assign(first, last);
				};

			vector(const vector& x): _array(nullptr), _size(0), _capacity(0), _alloc(x._alloc)
			{
				if (&x != this)
					*this = x;
			};

			~vector()
			{
				if (_array != nullptr)
				{
					clear();
					_alloc.deallocate(_array, _capacity);
				}
			};
			vector& operator=(const vector& x)
			{
				if (&x != this)
					assign(x.begin(), x.end());
				return (*this);
			};

			/* assign function */
			template <class InputIterator>
			typename enable_if <!is_integral<InputIterator>::value, void>::type
				assign(InputIterator first, InputIterator last)
				{	
					clear();
					insert(begin(), first, last);				
				};
			void assign (size_type n, const_reference u)
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
				return (reverse_iterator(--end()));
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
				_allocate_copy_assign(n);
			};
			void shrink_to_fit()
			{
				if (!(_capacity > _size))
					return ;
				// creare un nuovo vettore, copiarlo e liberare quello vecchio
				if (!_size && _array)
				{
					_alloc.deallocate(_array, _capacity);
					_array = nullptr;
					_capacity = 0;
					return ;
				}
				_allocate_copy_assign(_size);
			};

			// No bounds checking is performed on operator[]
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
				if (!(0 <= n && n < _size))
					throw (std::out_of_range("index out of range"));
				return (_array[n]);
			};
			const_reference at(size_type n) const
			{
				if (!(0 <= n && n < _size))
					throw (std::out_of_range("index out of range"));
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

			// Calling front or back on an empty container causes undefined behavior.
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

			void push_back(const_reference x)
			{
				insert(end(), x);
			};
			void pop_back()
			{
				if (!_size)
					return ;
				_alloc.destroy(&_array[--_size]);
			};
			iterator insert(iterator position, const_reference x)
			{
				if (!_capacity)
				{
					_array = _alloc.allocate(1);
					_capacity = 1;
					_alloc.construct(&_array[_size++], x);
					return (iterator(_array));
				}
				if (_size < _capacity)
				{
					iterator it = end();
					if (position == it)
						_alloc.construct(it.base(), x);
					else
					{
						_alloc.construct(it.base(), *(it - 1));
						--it;
						for ( ; it != position; --it)
							*it = *(it - 1);
						*it = x;
					}
					++_size;
					return (position);
				}
				difference_type offset = position.base() - cbegin().base();
				_allocate_copy_assign(_size * 2);
				return (insert(_array + offset, x));
			};
			iterator insert(iterator position, size_type n, const_reference x)
			{
				for (size_type i = 0; i < n; i++)
					position = insert(position, x).base();
				return (position);
			};
			template <class InputIterator>
				typename enable_if <!is_integral<InputIterator>::value, iterator>::type
				insert(iterator position, InputIterator first, InputIterator last)
				{
					if (first != last)
					{
						InputIterator it = last;
						while (--it != first)
							position = insert(position, *it).base();
						position = insert(position, *it).base();
					}
					return (position);
				};
			iterator erase(iterator position)
			{
				iterator ps = position;
				_alloc.destroy(ps.base());
				difference_type offset = position.base() - cbegin().base();
				for( ; static_cast<unsigned long>(offset) < _size - 1; offset++)
					_array[offset] = _array[offset + 1];
				--_size;
				return (ps);
			};
			iterator erase(iterator first, iterator last)
			{
				for (iterator it = first; it != last; ++it)
					erase(first);
				return (first);
			};

			void clear()
			{
				erase(begin(), end());
			};
			void resize(size_type sz, const value_type& c = value_type())
			{
				while (_size < sz)
					push_back(c);
				while (_size > sz)
					pop_back();
			};

			void swap(vector& x)
			{
				swap(this->_array, x._array);
				swap(this->_size, x._size);
				swap(this->_capacity, x._capacity);
			};
		
		private:
			pointer			_array;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

			void _allocate_copy_assign(size_type size)
			{
				pointer _new_array = _alloc.allocate(size);
				if (_array)
				{
					// copy element and destruct it
					for (unsigned long i=0; i<_size; i++)
					{
						_alloc.construct(_new_array + i, _array[i]);
						_alloc.destroy(&(_array[i]));
					}
					_alloc.deallocate(_array, _capacity);
				}
				_capacity = size;
				_array = _new_array;
			}

			/*iterator _make_iter(const_iterator iter)
			{
				difference_type offset = iter.base() - cbegin().base();
    			return (iterator(begin() + offset));
			}*/
	};

	/* non-member funcs */
	template <class T> bool operator==(const vector<T>& x, const vector<T>& y)
	{
		if (x.size() != y.size())
			return (false);
		return (equal(x.begin(), x.end(), y.begin()));
	};
	template <class T> bool operator!=(const vector<T>& x, const vector<T>& y)
	{
		return (!(x == y));
	};
	template <class T> bool operator< (const vector<T>& x, const vector<T>& y)
	{
		return (lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	};
	template <class T> bool operator> (const vector<T>& x, const vector<T>& y)
	{
		return (y < x);
	};
	template <class T> bool operator>=(const vector<T>& x, const vector<T>& y)
	{
		return (!(x < y));
	};
	template <class T> bool operator<=(const vector<T>& x, const vector<T>& y)
	{
		return (!(y < x));
	};

	template <class T> void swap(const vector<T>& x, const vector<T>& y)
	{
		x.swap(y);
	};

	template <class T>
	std::ostream &operator<<(std::ostream &out, vector<T> &vec)
	{
		out <<"[";
		for(ft::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
		out << *it <<" ";
		out << "]";
		return (out);
	}

};

#endif