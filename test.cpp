/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
/* #include "VectorIterator.hpp"
#include "iterator.hpp"
#include "Vector.hpp"
#include "Stack.hpp" */
#include <map>
# include "BaseTree.hpp"
# include "pair.hpp"



template <class T>
struct min_pair
{
	bool operator()(const T& x, const T& y) const
	{
		//std::cout << "--------------MIN--------------" << std::endl;
		return x < y;
	}
};

template <class T>
struct max
{
	bool operator()(const T& x, const T& y) const
	{
		//std::cout << "--------------MAX--------------" << std::endl;
		return x > y;}
};



int main() {
	
	typedef ft::pair<std::string, int> _p;
	_p p1("ciao", 3);
	_p p2("paco", 6);
	_p p3("ale", 16);
	_p p4("taco", 66);
	_p p5("uli", 166);
	_p p6("va", 166);
	_p p7("za", 166);
	_p p8("baci", 166);
	_p p9("bz", 166);

	ft::base_tree<_p> tree;
	std::cout << "--------------TREE--------------" << std::endl;
	std::cout << "--------------p1--------------" << std::endl;
	std::cout << *tree.insert(p1) << std::endl;
	std::cout << "--------------p2--------------" << std::endl;
	std::cout << *tree.insert(p2) << std::endl;
	std::cout << "--------------p3--------------" << std::endl;
	std::cout << *tree.insert(p3) << std::endl;
	std::cout << "--------------p4--------------" << std::endl;
	std::cout << *tree.insert(p4) << std::endl;
	std::cout << "--------------p5--------------" << std::endl;
	std::cout << *tree.insert(p5) << std::endl;
	std::cout << "--------------p6--------------" << std::endl;
	std::cout << *tree.insert(p6) << std::endl;
	std::cout << "--------------p7--------------" << std::endl;
	std::cout << *tree.insert(p7) << std::endl;
	std::cout << "--------------p8--------------" << std::endl;
	std::cout << *tree.insert(p8) << std::endl;
	std::cout << "--------------p9--------------" << std::endl;
	std::cout << *tree.insert(p9) << std::endl;
	//tree.root_pointer = tree.create_node(p1);
	std::cout << "--------------ROOT--------------" << std::endl;
	std::cout << *tree.root_pointer << std::endl;
	std::cout << "L" << *tree.root_pointer->left << std::endl;
	std::cout << "R" << *tree.root_pointer->right << std::endl;
	std::cout << "RR" << *tree.root_pointer->right->right << std::endl;
	std::cout << "RL" << *tree.root_pointer->right->left << std::endl;
	std::cout << "RRR" << *tree.root_pointer->right->right->right << std::endl;
	std::cout << "RRL" << *tree.root_pointer->right->right->left << std::endl;
	std::cout << "______LEFT______" << std::endl;
	std::cout << "LR" << *tree.root_pointer->left->right << std::endl;
	std::cout << "LL" << *tree.root_pointer->left->left << std::endl;


	std::cout << "--------------DELETE--------------" << std::endl;
	tree.erase(tree.find("taco"));
	/* tree.erase(tree.find_node(p5));
	tree.erase(tree.find_node(p6));
	tree.erase(tree.find_node(p2));
	tree.erase(tree.find_node(p4)); */

	//tree.clear_all();
	std::cout << "--------------ROOT DELETE--------------" << std::endl;
	std::cout << tree.root_pointer << std::endl;

	std::cout << "L" << *tree.root_pointer->left << std::endl;
	std::cout << "R" << *tree.root_pointer->right << std::endl;
	std::cout << "RR" << *tree.root_pointer->right->right << std::endl;
	std::cout << "RL" << *tree.root_pointer->right->left << std::endl;
	std::cout << "RLR" << *tree.root_pointer->right->left->right << std::endl;
	//std::cout << "RRR" << *tree.root_pointer->right->right->right << std::endl;
	//std::cout << "RRL" << *tree.root_pointer->right->right->left << std::endl;
	//std::cout << "______LEFT______" << std::endl;
	//std::cout << "LR" << *tree.root_pointer->left->right << std::endl;
	//std::cout << "LL" << *tree.root_pointer->left->left << std::endl;
	
	



	//_p p1("ciao", 3);
	//tree.insert(p1);


	/* int const a[5] = {1,2,3,4,5};	
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
		
	ft::vector<int> vec;
	ft::vector<int> vec2;


	std::cout << "--------------VECTOR--------------" << std::endl;
	vec.push_back(5);
	vec.push_back(50);
	vec.push_back(500);

	vec2.push_back(4);
	vec2.push_back(40);
	vec2.push_back(400);
	vec2.push_back(4000);
	
	std::cout << "--------------SIZE--------------" << std::endl;
	std::cout << "vector ("<< vec.size() << "): " << vec << std::endl;
	std::cout << "vector2 ("<< vec2.size() << "): " << vec2 << std::endl;

	std::cout << "--------------SWAP--------------" << std::endl;

	vec.swap(vec2);
	std::cout << "vector ("<< vec.size() << "): " << vec << std::endl;
	std::cout << "vector2 ("<< vec2.size() << "): " << vec2 << std::endl;

	std::cout << "--------------POP BACK--------------" << std::endl;

	vec.pop_back();
	std::cout << "vector ("<< vec.size() << "," << vec.capacity()<<"): " << vec << std::endl;
	std::cout << "vector2 ("<< vec2.size() << "," << vec2.capacity()<<"): " << vec2 << std::endl;

	std::cout << "--------------INSERT V in front of V2--------------" << std::endl;
	vec2.insert(vec2.cbegin(), vec.begin(), vec.rbegin().base());
	std::cout << "vector ("<< vec.size() << "): " << vec << std::endl;
	std::cout << "vector2 ("<< vec2.size() << "): " << vec2 << std::endl;

	std::cout << "--------------STACK--------------" << std::endl;
	ft::stack<int,ft::vector<int> > s;
	s.push(5);
	s.push(50);
	s.push(500);
	std::cout << "--------------TOP--------------" << std::endl;
	std::cout << s.top() << std::endl;

	std::cout << "--------------POP--------------" << std::endl;
	s.pop();
	std::cout << s.top() << std::endl; */
}
