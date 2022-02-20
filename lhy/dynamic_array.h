#ifndef _ARRAY_H_
#define _ARRAY_H_ 
#include <iostream>
using namespace std;
static int DEFAULT_ELTS = 10;
class IntSetEmpty {};

template <class T>
class IntSet {
protected:
    T *elts;
    int sizeElts;
    int numElts;
    void copyFrom(const IntSet& is);
    bool isEmpty() const {return (this->numElts == 0);}
public: 
    IntSet (int size =  DEFAULT_ELTS);
    IntSet (const IntSet<T> &is);
    IntSet<T> &operator=(const IntSet<T>& is);
    IntSet<T> &operator+=(const IntSet<T>& is);
    ~IntSet();
    virtual void push(const T& leaf);
    virtual T remove();
    virtual int getSize() const {return this->sizeElts;}
    virtual void getContent() const {if (!this->isEmpty()) for (int num = 0; num < this->numElts; num++) cout << this->elts[num] << endl;}
};

template <class T>
class IntSetFront: public IntSet<T>{
protected:
    T *elts;
    int sizeElts;
    int numElts;
    void copyFrom(const IntSetFront& is);
    bool isEmpty() const {return (this->numElts == 0);}
public:
    IntSetFront (int size =  DEFAULT_ELTS);
    IntSetFront (const IntSetFront<T> &is);
    IntSetFront<T> &operator=(const IntSetFront<T>& is);
    IntSetFront<T> &operator+=(const IntSetFront<T>& is);
    ~IntSetFront();
    void push(const T& leaf) override;
    T remove() override;
    int getSize() const override {return this->sizeElts;}
    void getContent() const override {if (!this->isEmpty()) for (int num = 0; num < this->numElts; num++) cout << this->elts[num] << endl;}
};

#include "dynamic_impl.h"

#endif
