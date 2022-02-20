//
// Created by 肖斯琪 on 2020/12/3.
//

#ifndef PROJECT5_DLIST_IMPL_H
#define PROJECT5_DLIST_IMPL_H

template <class T>
bool Dlist<T>::isEmpty() const{
    return !first;
}

template <class T>
void Dlist<T>::insertFront(T *op) {
    node *np=new node;
    np->prev=nullptr;
    np->op=op;
    if(isEmpty()){
        np->next= nullptr;
        first=last=np;
    }
    else{
        np->next=first;
        first->prev=np;
        first=np;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op) {
    node *np=new node;
    np->next= nullptr;
    np->op=op;
    if(isEmpty()){
        np->prev= nullptr;
        first=last=np;
    }
    else{
        np->prev=last;
        last->next=np;
        last=np;
    }
}

template <class T>
T* Dlist<T>::removeFront() {
    if(!isEmpty()){
        node *victim;
        victim=first;
        T* result;
        if(victim->next== nullptr){
            first=last= nullptr;
        }
        else{
            first=victim->next;
            first->prev= nullptr;
        }
        result=victim->op;
        delete victim;
        return result;
    }
   else{
       emptyList e;
        throw e;
   }
}

template <class T>
T* Dlist<T>::removeBack() {
    if(!isEmpty()){
        node *victim;
        victim=last;
        T* result;
        if(victim->prev== nullptr){
            first=last= nullptr;
        }
        else{
            last=victim->prev;
            last->next= nullptr;
        }
        result=victim->op;
        delete victim;
        return result;
    }
    else{
        emptyList e;
        throw e;
    }
}

template <class T>
Dlist<T>::Dlist()
        :first(nullptr),last(nullptr)
{
}


template <class T>
Dlist<T>::Dlist(const Dlist &l):first(nullptr),last(nullptr){
    if(!l.isEmpty()){
        node *victim=l.first;
        while(victim){
            this->insertBack(victim->op);
            victim=victim->next;
        }
    }
}

template <class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l) {
    if(this!=&l) {
        this->copyAll(l);
    }
        return *this;
}

template <class T>
Dlist<T>::~Dlist<T>() {
    removeAll();
}

template <class T>
void Dlist<T>::removeAll() {
    while(!isEmpty()){
        T* det;
        det=removeFront();
        delete det;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    if (this != &l) {
        removeAll();
        if(!l.isEmpty()){
            node *victim = l.first;
            while (victim) {
                this->insertBack(victim->op);
                victim = victim->next;
            }
        }
        else{
            first=last= nullptr;
        }
    }
}
#endif //PROJECT5_DLIST_IMPL_H
