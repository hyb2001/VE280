//
// Created by hyb_2001 on 2020/11/15.
//

#include "clause.h"
#include "cnf.h"
#include "iostream"

using namespace std;

CNF::CNF():numClauses(0),numVars(0){}

void CNF::addClause(Clause cls){
    clauses[numClauses]=cls;
    numClauses++;
}

void CNF::eliminate(Literal literal) {
    for (int i = 0; i < (int)numClauses; ++i) {
        clauses[i].eliminate(literal);
    }
}

int CNF::evaluate(const int val[]) const{
    int flag=0;
    int ans;
    //if 0, return 0; if -1, remember
    for (int i = 0; i < (int)numClauses; ++i) {
        ans=clauses[i].evaluate(val);
        if (ans==-1) flag=-1;
        if (ans==0) return 0;
    }
    if (flag==-1) return -1;
    return 1;
}

bool CNF::hasUnit() const {
    for (int i = 0; i < (int)numClauses; ++i) {
        if (clauses[i].getNumLiterals()==1) return true;
    }
    return false;
}

Literal CNF::getUnit() const {
    Literal ne;
    for (int i = 0; i < (int)numClauses; ++i) {
        if (clauses[i].getNumLiterals()==1) {
            return clauses[i].getLiteral(0);
        }
    }
    return ne;
}

CNF CNF::unitPropagate(Literal unit, int val[]) const{
    //eliminate unit
    val[unit.ID]=1-unit.negative;
    CNF now=*this;
    now.eliminate(unit);
    return now;
}

void CNF::print() const{
    for (int i = 0; i < (int)numClauses-1; ++i) {
        clauses[i].print();
        cout<<" & ";
    }
    clauses[numClauses-1].print();
    cout<<endl;
}

unsigned int CNF::getNumVars() const{
    return numVars;
}

unsigned int CNF::getNumClauses() const{
    return numClauses;
}

void CNF::setNumVars(unsigned int n){
    numVars=n;
}

CNF::~CNF(){
    numVars=0;
    numClauses=0;
}
