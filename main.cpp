#include <iostream>
#include <string>
#include <deque>

#include <chrono> // since C++ 11 , used only to compare ft and stl container speed

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include "includes/map.hpp"
	#include "includes/stack.hpp"
	#include "includes/vector.hpp"
	#include "includes/set.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	#ifndef STL
		ft::stack<Buffer, std::deque<int> > stack_deq_buffer;
	#endif
	ft::map<int, int> map_int;
	ft::set<int> set_int;

	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	/*
		VECTOR
	*/
	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer[i].idx = i + rand();
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = (rand() + i) % COUNT;
		sum += vector_buffer[access].idx;
	}

	std::cout << "sum from vector elements: " << sum << std::endl;
	
	ft::vector<Buffer>::iterator it_vector = vector_buffer.begin();
	int tmp = (*it_vector).idx;

	ft::vector<Buffer> vector_int2;
	vector_int2.swap(vector_buffer);
	if ((*it_vector).idx != tmp)
		std::cerr << "Error: THIS ITERATOR SHOULD BE VALID!!" <<std::endl;

	if (vector_buffer.begin() != vector_buffer.cend())
		std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	end = std::chrono::steady_clock::now();
	std::cout << "***Vector operations time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]***" << std::endl;
	/*
		MAP
	*/
	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}
	sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand() + i;
		sum += map_int[access];
	}

	std::cout << "sum from map elements: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	end = std::chrono::steady_clock::now();
	std::cout << "***Map operations time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]***" << std::endl;
	/*
		STACK
	*/
	begin = std::chrono::steady_clock::now();

	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}

	std::cout << std::endl;

	end = std::chrono::steady_clock::now();
	std::cout << "***Stack operations time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]***" << std::endl;
	/*
		SET
	*/
	begin = std::chrono::steady_clock::now();
	for (int i = 0; i < COUNT; ++i)
	{
		set_int.insert(rand());
	}
	sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand() + i;
		if (set_int.find(access) != set_int.cend())
			sum += *(set_int.find(access));
	}

	std::cout << "sum from set elements: " << sum << std::endl;

	{
		ft::set<int> copy = set_int;
	}
	end = std::chrono::steady_clock::now();
	std::cout << "***Set operations time = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " [µs]***" << std::endl;

	return (0);
}