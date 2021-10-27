
#ifndef STACK_HPP
# define STACK_HPP

# include "utils.hpp"
# include "vector.hpp"

namespace ft
{
	template < class T, class Container = vector<T> >
	class stack
	{
	public:
		typedef Container                                container_type;
		typedef typename container_type::value_type      value_type;
		typedef typename container_type::reference       reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::size_type       size_type;

	protected:
		/*-------------------ATTRIBUTES-------------------*/
		container_type c;

	public:
		/*-------------------CONSTRUCTURS-------------------*/
		stack() : c() {};
		stack(const stack& q) : c(q.c) {}
		explicit stack(const container_type& _c) : c(_c) {};

		stack& operator=(const stack& q)
		{
			c = q.c;
			return (*this);
		};

		~stack() {};

		template <class Alloc>
			explicit stack(const Alloc& a) : c(a) {};
		template <class Alloc>
			stack(const container_type& _c, const Alloc& a) : c(_c, a) {};
		template <class Alloc>
			stack(const stack& q, const Alloc& a) : c(q.c, a) {};

		bool empty() const
		{
			return (c.empty());
		};
		size_type size() const
		{
			return (c.size());
		};
		reference top()
		{
			return (c.back());
		};
		const_reference top() const
		{
			return (c.back());
		};

		void push(const value_type& x)
		{
			c.push_back(x);
		};
		void pop()
		{
			c.pop_back();
		};

		void swap(stack& q)
		{
			ft::swap(c, q.c);
		}
		template <class T1, class C1>
		friend bool operator==(const stack<T1, C1>& x, const stack<T1, C1>& y);

		template <class T1, class C1>
		friend bool operator< (const stack<T1, C1>& x, const stack<T1, C1>& y);
		
	}; // class stack

	/*-------------------OPERATORS-------------------*/
			/*---------LOGIC OPERATOR---------*/
	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (x.c == y.c);
	};
	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (x.c < y.c);
	};
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(x == y));
	};
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (y < x);
	};
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(x < y));
	};
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y)
	{
		return (!(y < x));
	};

	template <class T, class Container>
	void swap(stack<T, Container>& x, stack<T, Container>& y)
	{
		x.swap(y);
	};
}; // namespace ft

#endif