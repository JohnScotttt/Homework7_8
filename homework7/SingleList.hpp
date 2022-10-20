#pragma once
#include<iostream>
#include"ListNode.hpp"

template <typename T>
class SingleList
{
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T), int);
	void copyArray(T const*, Rank, int);

public:
	SingleList() { init(); }
	SingleList(SingleList<T> const& L);
	SingleList(SingleList<T> const& L, Rank r, int n);
	SingleList(ListNodePosi(T) p, int n);
	SingleList(T const* A, int n);
	SingleList(T const* A, Rank f, int n);

	~SingleList();

	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;
	ListNodePosi(T) first() const { return header->succ; }

	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) reverse();
	T remove(ListNodePosi(T) p);

	void traverse(void (*)(T&));
	template <typename VST> void traverse(VST&);
};

template <typename T>
ListNodePosi(T) next(ListNodePosi(T)& p);

template <typename T>
void swap(T& n, T& m);

template <typename T>
struct Show
{
	void operator()(T& e) {
		std::cout << e;
	}
};


template <typename T>
inline void SingleList<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer;
	trailer->succ = NULL;
	_size = 0;
}

template<typename T>
inline int SingleList<T>::clear()
{
	int oldSize = _size;
	while (1 < _size) remove(header->succ);
	trailer = header->succ;
	remove(trailer);
	return oldSize;
}

template<typename T>
inline void SingleList<T>::copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
inline void SingleList<T>::copyArray(T const* A, Rank f, int n)
{
	init();
	while (n--)
	{
		insertAsLast(A[f]);
		f++;
	}
}

template<typename T>
inline SingleList<T>::SingleList(SingleList<T> const& L) { copyNodes(L.first(), L._size); }

template<typename T>
inline SingleList<T>::SingleList(SingleList<T> const& L, Rank r, int n) { copyNodes(L[r], n); }

template<typename T>
inline SingleList<T>::SingleList(ListNodePosi(T) p, int n) { copyNodes(p, n); }

template<typename T>
inline SingleList<T>::SingleList(T const* A, int n) { copyArray(A, 0, n); }

template<typename T>
inline SingleList<T>::SingleList(T const* A, Rank f, int n) { copyArray(A, f, n); }

template<typename T>
inline SingleList<T>::~SingleList()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
inline T& SingleList<T>::operator[](Rank r) const
{
	ListNodePosi(T) p = first();
	while (0 < r--) p = p->succ;
	return p->data;
}


template<typename T>
inline ListNodePosi(T) SingleList<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
inline ListNodePosi(T) SingleList<T>::insertAsLast(T const& e)
{
	_size++;
	ListNodePosi(T) p = trailer->insertAsPred(e);
	trailer = trailer->succ;
	return p;
}

template<typename T>
inline ListNodePosi(T) SingleList<T>::insertAfter(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
inline ListNodePosi(T) SingleList<T>::insertBefore(ListNodePosi(T) p, T const& e)
{
	_size++;
	if (p != trailer) return p->insertAsPred(e);
	else
	{
		ListNodePosi(T) t = trailer->insertAsPred(e);
		trailer = trailer->succ;
		return t;
	}
}

template<typename T>
inline ListNodePosi(T) SingleList<T>::reverse()
{
	Rank lo = 0;
	Rank hi = _size - 1;
	while (lo < hi) swap((*this)[lo++], (*this)[hi--]);
	return this->first();
}

template<typename T>
inline T SingleList<T>::remove(ListNodePosi(T) p)
{
	T e = p->data;
	p->data = p->succ->data;
	ListNodePosi(T) t = p->succ;
	p->succ = p->succ->succ;
	delete t;
	_size--;
	return e;
}

template<typename T>
inline void SingleList<T>::traverse(void(*)(T&))
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
template<typename VST>
inline void SingleList<T>::traverse(VST& visit)
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template <typename T>
ListNodePosi(T) next(ListNodePosi(T)& p)
{
	p = p->succ;
	return p;
}

template <typename T>
inline void swap(T& n, T& m)
{
	T tmp = n;
	n = m;
	m = tmp;
}
