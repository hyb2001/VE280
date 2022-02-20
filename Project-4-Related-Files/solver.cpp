//
// Created by hyb_2001 on 2020/11/16.
//

#include "cnf.h"
#include "iostream"
#include "solver.h"

using namespace std;

class EnumSolver: public Solver{
private:
    bool solvehelper(const CNF &cnf,int num,int val[]);
    //MODIFY:val
    //EFFECT: Find which val[] can make the cnf SAT

public:
    void solve(const CNF &cnf);
    //EFFECT: Use solvehelper to operate "SAT

    void evaluate(const CNF &cnf, const int val[]);
    //EFFECT:figure out the value of certain val[]
};

class DeductSolver: public Solver{
private:
    bool solvehelper(const CNF &cnf,int numclause,int numvars,CNF change,int val[]);
    //MODIFY: change val[]
    //EFFECT: Stimulate the deductive function of operating "SAT"

public:
    void solve(const CNF &cnf);
    //EFFECT: Use solvehelper to operate "SAT

    void evaluate(const CNF &cnf, const int val[]);
    //EFFECT:figure out the value of certain val[]
};

static EnumSolver enumSolver;
static DeductSolver deductSolver;
Solver *getEnum(){return &enumSolver;}
Solver *getDeduct(){return &deductSolver;}

bool EnumSolver::solvehelper(const CNF &cnf,int num,int val[]){
    if (num==(int)cnf.getNumVars() && cnf.evaluate(val)==1){
        //when all the variable are determined, test the val[]
        cout<<"The expression is SAT with one solution:"<<endl;
        for (int i = 0; i < (int)cnf.getNumVars()-1; ++i) {
            cout<<val[i]<<" ";
        }
        cout<<val[cnf.getNumVars()-1];
        cout<<endl;
        return true;
    }else if (num==(int)cnf.getNumVars()){
            return false;
        }else {
        //try 1 or 0
        val[num] = 0;
        if (solvehelper(cnf, num + 1, val)) return true;
        val[num] = 1;
        if (solvehelper(cnf, num + 1, val)) return true;
    }
    return false;
}

void EnumSolver::solve(const CNF &cnf){
    int var=cnf.getNumVars();
    CNF n;
    int val[var+1];
    for (int i = 0; i <= var; ++i) {
        val[i]=-1;
    }
    bool ans=solvehelper(cnf,0,val);
    if (!ans){
        cout<<"The expression is unSAT!"<<endl;
    }
}

void EnumSolver::evaluate(const CNF &cnf, const int val[]){
    int ans=cnf.evaluate(val);
    cout<<"The value of the Boolean expression is: ";
    if (ans==-1) {cout<<"Unknown"<<endl;}
    else if (ans==1) cout<<"True"<<endl;
    else cout<<"False"<<endl;
}

bool DeductSolver::solvehelper(const CNF &cnf,int numclause,int numvars,CNF change,int val[]) {
    int test = change.evaluate(val);
    int changed = 0;
    int ch[55];
    if (test == 1) {
        cout << "The expression is SAT!" << endl;
        return true;
    } else {
       // eliminate all the unit unknown
        while (change.hasUnit()) {
            Literal Unit;
            Unit = change.getUnit();
            cout << "Unit propagate x" << Unit.ID << " = " << 1 - Unit.negative << ":" << endl;
            ch[changed] = (int) Unit.ID;
            changed++;
            change = change.unitPropagate(Unit, val);
            change.print();
        }
        //test whether SAT
        int te = change.evaluate(val);
        if (te == 1) {
            cout << "The expression is SAT!" << endl;
            return true;
        }
        //find the left most unknown variable
        int dec = -1;
        for (int i = 0; i < numvars - 1; ++i) {
            if (val[i] == -1) {
                dec = i;
                break;
            }
        }
        if (dec != -1) {
            Literal Unit;
            CNF nchange;
            Unit.ID = dec;
            Unit.negative = true;
            //try 0 first
            cout << "Make decision x" << dec << " = 0:" << endl;
            val[dec] = 0;
            nchange = change.unitPropagate(Unit, val);
            nchange.print();
            if (solvehelper(cnf, numclause, numvars, nchange, val)) return true;
            else {
                // if not succeed, try 1
                val[dec] = 1;
                Unit.negative = false;
                cout << "Reverse previous decision x" << dec << " = 1:" << endl;
                nchange = change.unitPropagate(Unit, val);
                nchange.print();
                if (solvehelper(cnf, numclause, numvars, nchange, val)) return true;
                val[dec] = -1;
            }
        }
    }
    for (int i = 0; i < changed; ++i) {
        val[ch[i]] = -1;
    }
    return false;
}

void DeductSolver::solve(const CNF &cnf){
    cout<<"Start deductive solver for:"<<endl;
    cnf.print();
    int num=cnf.getNumClauses();
    int var=cnf.getNumVars();
    int val[var+1];
    for (int i = 0; i <= var; ++i) {
        val[i]=-1;
    }
    bool ans=solvehelper(cnf,num,var,cnf,val);
    if (!ans){
        cout<<"The expression is unSAT!"<<endl;
    }
}

void DeductSolver::evaluate(const CNF &cnf, const int val[]){
    //same as enum
    int ans=cnf.evaluate(val);
    cout<<"The value of the Boolean expression is: ";
    if (ans==-1) {cout<<"Unknown";}
    else if (ans==1) cout<<"True";
    else cout<<"False";
    cout<<endl;
}
