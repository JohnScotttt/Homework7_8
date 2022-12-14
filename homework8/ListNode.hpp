#pragma once
typedef int Rank;
#define ListNodePosi(T) ListNode<T>*

template <typename T>
struct ListNode
{
	T data;
	ListNodePosi(T) succ;
	ListNodePosi(T) pred;

	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr)
		: data(e), pred(p), succ(s) {}
	ListNodePosi(T) insertAsSucc(T const& e);
	ListNodePosi(T) insertAsPred(T const& e);
};

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x;
	succ = x;
	return x;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}
