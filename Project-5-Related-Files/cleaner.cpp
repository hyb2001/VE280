#include "dlist.h"
#include <iostream>
#include <string>
using namespace std;


struct command{
    int position;
    int status;//0:del 1:add 2:other
};

bool check(string command[], string order, int comn){
    for (int i = 0; i < comn; i++){
        if (order==command[i]) 
        return true;
    }
    return false;
}

int main() {
    int addn,deleten;
    cin >> addn;
    string add[1000];
    for (int i = 0; i < addn; ++i) {
        cin >> add[i];
        //read in add operation
    }
    cin >> deleten;
    string dele[1000];
    for (int i = 0; i < deleten; i++) {
        cin >> dele[i];
        //read in delete operation
    }
    string line="";
    string whole="";
    getline(cin, whole);
    while (getline(cin,whole)){
        line.append(whole);
        line.push_back('\n');
        whole.clear();
        //put all the input into one string
    }
    int length=line.size();
    bool comment=false;
    auto out= new bool[length];
    for (int i = 0; i < length; ++i) {
        out[i]=true;
        //mark the output status
    }
    auto stack=new Dlist<command>;
    for (int i = 0; i < length; ++i) {
        //initiate the cleaner
        if (!comment && line[i] =='{' && i>= 5 && check(add,line.substr(i-5,5),addn)){
            stack->insertBack(new command{i, 1});
            //push in
        }else if (!comment && line[i] =='{' && i>= 5 && check(dele,line.substr(i-5, 5), deleten)) {
            stack->insertBack(new command{i, 0});
            //push in
        }else if (!comment && line[i] =='{'&& (i == 0 || line[i - 1] != '\\')){
            stack->insertBack(new command{i, 2});
            //push in
        }else if (!comment && line[i] == '}' && (i == 0 || line[i - 1] != '\\') && !stack->isEmpty()) {
            //stack pop out
            command* com = stack->removeBack();
            if (com->status == 0) {
                for (int j = com->position-5; j<=i; j++) {
                    out[j]=false;
                }
            } else if (com->status == 1) {
                for (int j = com->position-5; j<= com->position; j++) {
                    out[j]=false;
                }
                    out[i]=false;
                }
            delete com;
            //update output status
        }else if (line[i] =='%' && (i==0 || line[i-1] != '\\')) {
            comment=true;
        }else if (line[i]=='\n'){
            comment=false;
        }
    }
    for (int j=0; j<length; j++) {
        if (out[j]) {
            cout << line[j];
            //output
        }
    }
    delete[] out;
    delete stack;
}

