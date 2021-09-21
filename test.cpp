/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include "VectorIterator.hpp"

using namespace std;



int main()
{
	int const a[5] = {1,2,3,4,5};
	int b[5] = {1,2,3,4,5};
	ft::ConstVectorIterator<int> ci(a);
	ft::ConstReverseVectorIterator<int> cr(&a[4]);
	ft::VectorIterator<int> i(b);
	ft::ReverseVectorIterator<int> r(&b[4]);
	std::cout << "CIT: " << ci[0] << " CRIT: " << cr[0] << "\n";
	std::cout << " IT: " << i[0] << "  RIT: " << r[0] << "\n";
	std::cout << "---------OPERATOR---------" << "\n";
	std::cout << "---------[++]---------" << "\n";
	ci++;
	i++;
	cr+=1;
	r+=1;
	std::cout << "CIT: " << ci[0] << " CRIT: " << cr[0] << "\n";
	std::cout << " IT: " << i[0] << "  RIT: " << r[0] << "\n";

}