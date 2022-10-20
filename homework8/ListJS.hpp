#pragma once
#include"ListNode.hpp"
#include<iostream>

template <typename T>
class ListJS
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
	ListJS() { init(); }
	ListJS(ListJS<T> const& L);
	ListJS(ListJS<T> const& L, Rank r, int n);
	ListJS(ListNodePosi(T) p, int n);
	ListJS(T const* A, int n);
	ListJS(T const* A, Rank f, int n);

	~ListJS();

	Rank size() const { return _size; }
	bool empty() const { return _size <= 0; }
	T& operator[] (Rank r) const;
	ListNodePosi(T) first() const { return header->succ; }
	ListNodePosi(T) last() const { return trailer->pred; }
	ListNodePosi(T) find(T const& e) const { return find(e, _size, trailer); }
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) search(T const& e) const { return search(e, _size, trailer); }
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p) const;
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }

	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertAfter(ListNodePosi(T) p, T const& e);
	ListNodePosi(T) insertBefore(ListNodePosi(T) p, T const& e);
	void insertionSort(ListNodePosi(T) p, int n);
	void reverse();
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
inline void ListJS<T>::init()
{
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->succ = NULL; trailer->pred = header;
	_size = 0;
}

template<typename T>
inline int ListJS<T>::clear()
{
	int oldSize = _size;
	while (0 < _size) remove(header->succ);
	return oldSize;
}

template<typename T>
inline void ListJS<T>::copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--)
	{
		insertAsLast(p->data);
		p = p->succ;
	}
}

template<typename T>
inline void ListJS<T>::copyArray(T const* A, Rank f, int n)
{
	init();
	while (n--)
	{
		insertAsLast(A[f]);
		f++;
	}
}

template<typename T>
inline ListJS<T>::ListJS(ListJS<T> const& L) { copyNodes(L.first(), L._size); }

template<typename T>
inline ListJS<T>::ListJS(ListJS<T> const& L, Rank r, int n) { copyNodes(L[r], n); }

template<typename T>
inline ListJS<T>::ListJS(ListNodePosi(T) p, int n) { copyNodes(p, n); }

template<typename T>
inline ListJS<T>::ListJS(T const* A, int n) { copyArray(A, 0, n); }

template<typename T>
inline ListJS<T>::ListJS(T const* A, Rank f, int n) { copyArray(A, f, n); }

template<typename T>
inline ListJS<T>::~ListJS()
{
	clear();
	delete header;
	delete trailer;
}

template<typename T>
inline T& ListJS<T>::operator[](Rank r) const
{
	ListNodePosi(T) p = first();
	while (0 < r--) p = p->succ;
	return p->data;
}


template<typename T>
inline ListNodePosi(T) ListJS<T>::find(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 < n--)
		if (e == (p = p->pred)->data)return p;
	return nullptr;
}

template<typename T>
inline ListNodePosi(T) ListJS<T>::search(T const& e, int n, ListNodePosi(T) p) const
{
	while (0 <= n--)
		if (((p = p->pred)->data) <= e) break;
	return p;
}

template<typename T>
inline ListNodePosi(T) ListJS<T>::selectMax(ListNodePosi(T) p, int n)
{
	ListNodePosi(T) max = p;
	for (ListNodePosi(T) cur = p; 1 < n; n--)
		if (!lt((cur = cur ->succ)->data, max->data))
			max = cur;
	return max;
}

template<typename T>
inline ListNodePosi(T) ListJS<T>::insertAsFirst(T const& e)
{
	_size++;
	return header->insertAsSucc(e);
}

template<typename T>
inline ListNodePosi(T) ListJS<T>::insertAsLast(T const& e)
{
	_size++;
	return trailer->insertAsPred(e);
}

template<typename T>
inline ListNodePosi(T) ListJS<T>::insertAfter(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsSucc(e);
}

template<typename T>
inline ListNodePosi(T) ListJS<T>::insertBefore(ListNodePosi(T) p, T const& e)
{
	_size++;
	return p->insertAsPred(e);
}

template<typename T>
inline void ListJS<T>::insertionSort(ListNodePosi(T) p, int n)
{
	for (int r= 0;r<n;r++)
	{
		insertAfter(search(p->data, r, p), p->data);
		p = p->succ;
		remove(p->pred);
	}
}

template<typename T>
inline void ListJS<T>::reverse()
{
	Rank lo = 0;
	Rank hi = _size - 1;
	while (lo < hi) swap((*this)[lo++], (*this)[hi--]);
}

template<typename T>
inline T ListJS<T>::remove(ListNodePosi(T) p)
{
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p;
	_size--;
	return e;
}

template<typename T>
inline void ListJS<T>::traverse(void(*)(T&))
{
	for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ) visit(p->data);
}

template<typename T>
template<typename VST>
inline void ListJS<T>::traverse(VST& visit)
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

