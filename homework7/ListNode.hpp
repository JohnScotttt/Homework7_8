#pragma once
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode
{
	T data;
	ListNodePosi(T) succ;

	ListNode() {}
	ListNode(T e, ListNodePosi(T) s = nullptr)
		: data(e), succ(s) {}
	ListNodePosi(T) insertAsSucc(T const& e);
	ListNodePosi(T) insertAsPred(T const& e);
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, succ);
	succ = x;
	return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi(T) x = new ListNode(data, succ);
	data = e;
	succ = x;
	return this;
}
