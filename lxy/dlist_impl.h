#include "dlist.h"

#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

template<class T>
Dlist<T>::Dlist():first(nullptr),last(nullptr){}

template<class T>
Dlist<T>::Dlist(const Dlist &l):first(nullptr),last(nullptr)
{
	copyAll(l);
}

template<class T>
bool Dlist<T>::isEmpty() const 
{
    return (first==nullptr);
}

template<class T>
void Dlist<T>::insertFront(T *op)
{
	node *np=new node;
	np->op=op;
	np->next=first;
	np->prev=nullptr;
	if (first!=nullptr) first->prev=np;
	first=np;
	if (last==nullptr) last=np;
}

template<class T>
void Dlist<T>::insertBack(T *op)
{
	node *np=new node;
	np->op=op;
	np->next=nullptr;
	np->prev=last;
	if (last!=nullptr) last->next=np;
	last=np;
	if (first==nullptr) first=np;
}

template<class T>
T *Dlist<T>::removeFront()
{
	if (isEmpty()) throw emptyList();
	node *victim=first;
	T *op;
	first=victim->next;
	if (first==nullptr) last=nullptr;
	op=victim->op;
	delete victim;
	return op;
}

template<class T>
T *Dlist<T>::removeBack()
{
	if (isEmpty()) throw emptyList();
	node *victim=last;
	T *op;
	last=victim->prev;
	if (last==nullptr) first=nullptr;
	op=victim->op;
	delete victim;
	return op;
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l)
{
	for (auto pt=l.first;pt!=l.last;pt=pt->next)
	{
		insertBack(pt.op);
		if (pt==l.first) first=last;
	}
	insertBack(l.last.op);
}

template<class T>
void Dlist<T>::removeAll()
{
	while (first!=nullptr)
	{
		node *victim=first;
		first=victim->next;
		delete victim;
	}
}

template<class T>
Dlist<T> &Dlist<T>::operator= (const Dlist &l)
{
	removeAll();
	copyAll(l);
	return *this;
}

template<class T>
Dlist<T>::~Dlist() 
{
    removeAll();
}

#endif