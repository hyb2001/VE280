//
// Created by hyb_2001 on 2020/11/30.
//
#ifndef VE280_DLIST_IMPL_H
#define VE280_DLIST_IMPL_H
//implementation of dlist

#include "iostream"
#include "dlist.h"

template<class T> bool Dlist<T>::isEmpty() const{
    return first==nullptr;
    //The empty list will have NULL first and last
}

template<class T> void Dlist<T>::insertFront(T *op){
    node* newnode=new node;
    newnode->op=op;
    if (isEmpty()){
        newnode->next=nullptr;
        newnode->prev=nullptr;
        first=newnode;
        last=newnode;
        //if empty, op will be only element
    }else{
        newnode->next=first;
        newnode->prev=nullptr;
        first->prev=newnode;
        first=newnode;
    }
}

template<class T> void Dlist<T>::insertBack(T *op){
    node* newnode=new node;
    newnode->op=op;
    if (isEmpty()){
        newnode->next=nullptr;
        newnode->prev=nullptr;
        first=newnode;
        last=newnode;
        //if empty, an emptylist will get
    }else{
        newnode->next=nullptr;
        newnode->prev=last;
        last->next=newnode;
        last=newnode;
    }
}


template<class T> T *Dlist<T>::removeFront(){
    if (!isEmpty()) {
        node* oldNode = first;
        if (oldNode == last) {
            first = nullptr;
            last = nullptr;
        } else {
            first = oldNode->next;
            first->prev = nullptr;
        }
        auto option = oldNode->op;
        delete oldNode;
        return option;
    }else{
        throw emptyList();
        //reduce wrong option
    }
}

template<class T> T *Dlist<T>::removeBack(){
    if (!isEmpty()) {
        node* oldNode = last;
        if (oldNode == first) {
            first = nullptr;
            last = nullptr;
        } else {
            last = oldNode->prev;
            last->next = nullptr;
        }
        auto option = oldNode->op;
        delete oldNode;
        return option;
    }else{
        throw emptyList();
        //reduce wrong option
    }
}

template<class T> Dlist<T>::Dlist(){
    first = last = nullptr;
    //constructor
}

template<class T> Dlist<T>::Dlist(const Dlist &l){
    last=first= nullptr;
    copyAll(l);
    //copy constructor
}

template<class T> Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    removeAll();
    copyAll(l);
    return *this;
    //operation assignment
}

template<class T> Dlist<T>::~Dlist(){
    removeAll();
    //destructor
}

template<class T> void Dlist<T>::removeAll(){
    if (!isEmpty())
    {
        auto t=first;
        while (t->next!= nullptr)
        {
            t = t->next;
            delete t->prev->op;
            delete t->prev;
        }
        delete t->op;
        delete t;
    }
    first = last = nullptr;
    // delete operation
}

template<class T> void Dlist<T>::copyAll(const Dlist &l){
    if (!l.isEmpty()){
        auto t = l.first;
        while (t->next!= nullptr){
            insertBack(t->op);
            t = t->next;
        }
        insertBack(t->op);
    }
    //deep copy
}

#endif