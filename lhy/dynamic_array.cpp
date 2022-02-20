#include <iostream>
#include "dynamic_array.h"
using namespace std;

int main(){
    IntSet<int>* a = new IntSet<int>(2);
    a->push(1);
    a->push(3);
    a->push(2);
    IntSet<int> b(*a);
    b += *a; 
    delete a; // needed
    cout << b.getSize() << endl << endl;
    cout << b.remove() << endl << endl;
    b.getContent();
    cout << endl;
    IntSetFront<int>* d = new IntSetFront<int>(2);
    d->push(1);
    d->push(2);
    d->push(3);
    d->getContent();
    cout << "!" << endl;
    IntSet<int> *c = d;
    c->getContent();
    cout << "!!" << endl;
    cout << c->getSize() << endl << endl;
    cout << c->remove() << endl << endl;
    cout << endl;
    delete c;
    int x = 4, y;
    (y = x) += 2;
    cout << y << endl;
    int *current = nullptr;
    cout << (current) << endl;
    delete current;
    return 0;
}
