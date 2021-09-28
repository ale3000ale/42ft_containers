/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include "VectorIterator.hpp"
#include "iterator.hpp"
#include "Vector.hpp"
#include "Stack.hpp"



int main() {
	/*int const a[5] = {1,2,3,4,5};	
	int b[5] = {1,2,3,4,5};
	ft::VectorIterator<const int*> ci(a);
	ft::reverse_iterator<ft::VectorIterator<const int*> > cr(&a[4]);
	ft::VectorIterator<int*> i(b);
	ft::reverse_iterator<ft::VectorIterator<int*> > r(&b[4]);
	std::cout << "--------------TEST--------------" << std::endl;
	std::cout << "VectorIterator (IT)  reverse_iterator (RIT) " << std::endl;
	std::cout << "Const VectorIterator (CIT)  Const reverse_iterator (CRIT) " << std::endl;
	std::cout << "CIT: " << ci[0] << " CRIT: " << cr[0] << std::endl;
	std::cout << " IT: " << i[0] << "  RIT: " << r[0] << std::endl;
	std::cout << "--------------OPERATOR--------------" << std::endl;

	std::cout << "---------[+]---------" << std::endl;
	ci++;
	i++;
	cr+=1;
	r+=1;
	std::cout << "CIT: " << ci[0] << " CRIT: " << cr[0] << std::endl;
	std::cout << " IT: " << i[0] << "  RIT: " << r[0] << std::endl;

	std::cout << "---------[-]---------" << std::endl;
	ci--;
	i--;
	cr-=1;
	r-=1;
	std::cout << "CIT: " << ci[0] << " CRIT: " << cr[0] << std::endl;
	std::cout << " IT: " << i[0] << "  RIT: " << r[0] << std::endl;

	std::cout << "---------[*]---------" << std::endl;
	std::cout << "CIT: " << *ci << " CRIT: " << *cr << std::endl;
	std::cout << " IT: " << *i << "  RIT: " << *r << std::endl;

	std::cout << "--------------ACCESSOR--------------" << std::endl;
	std::cout << "CIT: " << (ci < ci) << std::endl;
	std::cout << "C A:  " << a << "   B: " << b<< std::endl;
	std::cout << "CIT:  " << ci.base()  			<< "  IT: " << i.base() << std::endl;
	std::cout << "CRIT: " << cr.base().base()	<< " RIT: " << r.base().base() << std::endl;
		*/
	ft::vector<int> vec;

	std::cout << "--------------VECTOR--------------" << std::endl;
	vec.push_back(5);
	vec.push_back(50);
	vec.push_back(500);
	
	std::cout << "--------------SIZE--------------" << std::endl;
	std::cout << vec.size() << std::endl;

	std::cout << "--------------POP BACK--------------" << std::endl;
	std::cout << vec;
	vec.pop_back();
	std::cout << vec;


	std::cout << "--------------STACK--------------" << std::endl;
	ft::stack<int,ft::vector<int> > s;
	s.push(5);
	s.push(50);
	s.push(500);
	std::cout << "--------------TOP--------------" << std::endl;
	std::cout << s.top() << std::endl;

	std::cout << "--------------POP--------------" << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;

	std::cout << "--------------POP--------------" << std::endl;
	s.pop();
	std::cout << s.top() << std::endl;
	s.size();

}
