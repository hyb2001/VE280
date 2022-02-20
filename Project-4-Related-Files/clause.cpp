#include "clause.h"
#include "iostream"

using namespace std;

Clause::Clause():numLiterals(0),value(0){}

void Clause::addLiteral(Literal literal) {
    literals[numLiterals].ID=literal.ID;
    literals[numLiterals].negative=literal.negative;
    numLiterals++;
}

int Clause::evaluate(const int val[]) const{
    if (numLiterals==0){
        return value;
    }
    int flag=0;
    //if 1, return 1; if -1, remember it
    for (int i = 0; i < (int)numLiterals; i++) {
        if (val[literals[i].ID]+(literals[i].negative)==1) {
            return 1;
        }else if(val[literals[i].ID]==-1) {
            flag=-1;
        }
    }
    if (flag==-1){
        return -1;
    }
    return 0;
}

void Clause::eliminate(Literal literal){
    int now=0;
    //if the same return 1; if opposite, throw the literal
    for (int i = 0; i < (int)numLiterals; ++i) {
        if (i!=now){
            literals[now]=literals[i];
        }
        if (literal.ID==literals[now].ID){
            if (literal.negative==literals[now].negative){
                numLiterals=0;
                value=1;
                return;
            }
        }else{now++;}
    }
    if (now==0){
        if (numLiterals!=0){
            value=0;
        }
    }
    numLiterals=now;
}

void Clause::print() const {
    if (numLiterals==0) {
        cout<<"("<<value<<")";
    }else {
        cout<<"(";
        for (int i = 0; i < (int)numLiterals-1; ++i) {
            if (literals[i].negative) {
                cout<<"-";}
            cout<<"x"<<literals[i].ID<<" | ";
        }
        if (literals[numLiterals-1].negative) {
            cout<<"-";
        }
        cout<<"x"<<literals[numLiterals-1].ID<<")";
    }
}

unsigned int Clause::getNumLiterals() const{
    return numLiterals;
}

Literal Clause::getLiteral(unsigned int i) const {
    return literals[i];
}

Clause::~Clause(){
    numLiterals=0;
    value=0;
}