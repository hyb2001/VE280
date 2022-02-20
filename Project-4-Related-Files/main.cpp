//
// Created by hyb_2001 on 2020/11/18.
//


#include "solver.h"
#include "iostream"

using namespace std;

int main(int argc, char *argv[]){
    Solver *A;
    if ((string) argv[1] == "ENUM") {A=getEnum();}
    else {A=getDeduct();}
    int nvar,ncla;
    cin>>nvar>>ncla;
    CNF cnf;
    cnf.setNumVars(nvar);
    string s;
    getline(cin,s);
    for (int i = 0; i < ncla; ++i) {
        Clause cl;
        getline(cin,s);
        int len=s.size();
        int j=0;
        //read in the clause literal by literal
        while (j<len-1){
            bool fini=false;
            bool negative=false;
            int id=0;
            while (!fini) {
                char c;
                c = s[j];
                if (c == '-') negative=true;
                if (c=='|' || j==len-1) fini=true;
                if (c>='0' && c<='9') id=id*10+c-'0';
                j++;
            }
            Literal li;
            li.negative=negative;
            li.ID=id;
            cl.addLiteral(li);
        }
        cnf.addClause(cl);
    }
    bool finish=false;
    //do the operation
    while (!finish){
        cin>>s;
        if (s=="EXIT"){
            cout<<"Bye!"<<endl;
            finish=true;
        }
        if (s=="EVAL"){
            int val[100];
            for (int i = 0; i < nvar; ++i) {
                cin>>val[i];
            }
            A->evaluate(cnf,val);
        }
        if (s=="SAT"){
            A->solve(cnf);
        }
        if (s=="PRINT"){
            cnf.print();
        }
    }
}