#pragma once
#include"SingleList.hpp"

template <typename T>
class Solution
{
public:
	SingleList<T> addTwoNumbers(SingleList<T> const& l1, SingleList<T> const& l2);
};

template<typename T>
inline SingleList<T> Solution<T>::addTwoNumbers(SingleList<T> const& l1, SingleList<T> const& l2)
{
	Rank n = l1.size();
	bool flag = false;
	SingleList<T> res;
	ListNodePosi(T) num1 = l1.first();
	ListNodePosi(T) num2 = l2.first();
	while (n--)
	{
		T add = flag ? (num1->data + num2->data) % 10 + 1 : (num1->data + num2->data) % 10;
		res.insertAsLast(add);
		flag = (num1->data + num2->data) / 10 == 1;
		next(num1);
		next(num2);
	}
	return res;
}