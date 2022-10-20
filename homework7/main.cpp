#include<iostream>
#include"SingleList.hpp"
#include"Solution.hpp"
using namespace std;

int main()
{
	int num1[] = { 2,4,3 };
	int num2[] = { 5,6,4 };
	SingleList<int> l1(num1, 3);
	SingleList<int> l2(num2, 3);
	Solution<int> solution;
	SingleList<int> result = solution.addTwoNumbers(l1, l2);
	Show<int> show;
	result.reverse();
	result.traverse(show);
}