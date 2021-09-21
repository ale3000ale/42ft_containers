/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include "VectorIterator.hpp"

using namespace std;

class A
{
    
    
    public:
    int a;
    
        A(int _a) :a(_a){}
       virtual A operator+(int n)
        {
            A tmp(*this);
			tmp.a += n;
			return (tmp);
        }
        virtual A operator-(int n)
        {
            A tmp(*this);
			tmp.a -= n;
			return (tmp);
        }
        A & operator+=(int n)
		{
			*this = *this + n;
			return (*this);
		}
		A & operator-=(int n)
		{
			*this = *this - n;
			return (*this);
		}
        A & operator=(A const & other)
		{
			a = other.a;
			return (*this);
		}
};
        
class B : public A
{
    public:
        B(int _a) : A(_a){}
        A operator+(int n)
        {

            std::cout << "é +: " << a << "\n";
			return (A::operator-(n));
        }
        A operator-(int n)
        {
            return (A::operator+(n));
        }
};

int main()
{
    B ao(10);
    std::cout << "AO: " << ao.a << "\n";
    ao += 1;
    std::cout << "AO: " << ao.a << "\n";
}