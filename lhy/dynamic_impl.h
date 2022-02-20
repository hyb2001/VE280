#ifndef __DYNAMIC_IMPL__
#define __DYNAMIC_IMPL__

#include "dynamic_array.h"
template <class T>
IntSet<T> &IntSet<T>::operator= (const IntSet<T> &is){
    if (this != &is) this->copyFrom(is);
    return *this;
}

template <class T>
IntSet<T> &IntSet<T>::operator+= (const IntSet<T> &is){
    int tempSize = sizeElts;
    while (tempSize < numElts + is.numElts){
        if (tempSize == 0) tempSize = 1;
        else tempSize *= 2;
    }
    sizeElts = tempSize;
    int* newelts = new T[sizeElts];
    for (int num = 0; num < numElts; num++){newelts[num] = elts[num];}
    for (int num = 0; num < is.numElts; num++) {newelts[num+numElts] = is.elts[num];}
    delete [] elts;
    elts = newelts;
    numElts += is.numElts; 
    return *this;
}

template <class T>
void IntSet<T>::copyFrom(const IntSet<T> &is){
    if (is.sizeElts != this->sizeElts){
        delete [] elts;
        sizeElts = is.sizeElts;
        elts = new T[sizeElts];
    }
    for (int num = 0; num < is.numElts; num++){elts[num] = is.elts[num];}
    numElts = is.numElts;
}

template <class T>
void IntSet<T>::push(const T& leaf){
    if (numElts >= sizeElts){
        sizeElts *= 2;
        int *newelts = new T[sizeElts];
        for (int num = 0; num < numElts; num++){newelts[num] = elts[num];}
        delete [] elts;
        elts = newelts;
    } 
    elts[numElts++] = leaf; 
}

template <class T>
T IntSet<T>::remove(){
    if (this->isEmpty()) throw IntSetEmpty();
    else {T result = elts[(numElts--) - 1]; return result;}
}

template <class T> 
IntSet<T>::IntSet(int size): elts(new T[size]), sizeElts(size), numElts(0){}

template <class T>
IntSet<T>::IntSet(const IntSet<T> &is){
    elts = nullptr;
    sizeElts = 0;
    numElts = 0;
    copyFrom(is);
}
template <class T>
IntSet<T>::~IntSet(){delete [] elts;}





template <class T>
IntSetFront<T> &IntSetFront<T>::operator= (const IntSetFront<T> &is){
    if (this != &is) this->copyFrom(is);
    return *this;
}

template <class T>
IntSetFront<T> &IntSetFront<T>::operator+= (const IntSetFront<T> &is){
    int tempSize = sizeElts;
    while (tempSize < numElts + is.numElts){
        if (tempSize == 0) tempSize = 1;
        else tempSize *= 2;
    }
    sizeElts = tempSize;
    int* newelts = new T[sizeElts];
    for (int num = 0; num < numElts; num++){newelts[num] = elts[num];}
    for (int num = 0; num < is.numElts; num++) {newelts[num+numElts] = is.elts[num];}
    delete [] elts;
    elts = newelts;
    numElts += is.numElts; 
    return *this;
}

template <class T>
void IntSetFront<T>::copyFrom(const IntSetFront<T> &is){
    if (is.sizeElts != this->sizeElts){
        delete [] elts;
        sizeElts = is.sizeElts;
        elts = new T[sizeElts];
    }
    for (int num = 0; num < is.numElts; num++){elts[num] = is.elts[num];}
    numElts = is.numElts;
}

template <class T>
void IntSetFront<T>::push(const T& leaf) {
    if (numElts >= sizeElts){
        sizeElts *= 2;
        int *newelts = new T[sizeElts];
        for (int num = numElts ; num > 0; num--){newelts[num] = elts[num - 1];}
        delete [] elts;
        elts = newelts;
    } 
    else {
        for (int num = numElts ; num > 0; num--){elts[num] = elts[num - 1];}
    }
    (this->numElts)++;
    elts[0] = leaf; 
}

template <class T>
T IntSetFront<T>::remove() {
    if (this->isEmpty()) throw IntSetEmpty();
    else {
        T result = elts[0];
        for (int num = 1; num < numElts; num++) elts[num - 1] = elts[num]; 
        return result;
    }
}

template <class T> 
IntSetFront<T>::IntSetFront(int size): elts(new T[size]), sizeElts(size), numElts(0){}

template <class T>
IntSetFront<T>::IntSetFront(const IntSetFront<T> &is){
    elts = nullptr;
    sizeElts = 0;
    numElts = 0;
    copyFrom(is);
}
template <class T>
IntSetFront<T>::~IntSetFront(){delete [] elts;}

#endif