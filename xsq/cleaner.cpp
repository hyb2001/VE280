//
// Created by 肖斯琪 on 2020/12/3.
//

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
using namespace std;

class Bigthing{
    int position;
    bool isadd;
    bool isdel;
public:
    bool Isadd(){
        return isadd;
    }
    bool Isdel(){
        return isdel;
    }
    int Position(){
        return position;
    }
    Bigthing():position(0),isadd(false),isdel(false){
    }
    ~Bigthing(){}
    void Set(int p,bool add,bool del){
        position=p;
        isadd=add;
        isdel=del;
    }
};



int main() {
    int n, m;
    string nouse;
    cin >> n;//add number
    string *nameadd = new string[n];
    for (int i = 0; i < n; i++) {
        cin >> nameadd[i];
    }
    getline(cin, nouse);
    cin >> m;//del number
    string *namedel = new string[m];
    for (int i = 0; i < m; i++) {
        cin >> namedel[i];
    }
    getline(cin, nouse);

    string line,whole;
    while(getline(cin,line)){
        if(whole!=""){
            whole+='\n';
        }
        whole+=line;
    }

    Dlist<Bigthing> Find;
    char a;
    int index = 0;
    bool isescaped=false;
    while (whole[index]) {
        a=whole[index];
        if(isescaped){
            if(a=='\\'){
                string match(whole,index,2);
                if(match=="\n"){
                    index+=1;
                    isescaped=false;
                }
            }
        }
        if (a == '%') {
            index+=1;
            isescaped=true;
            continue;
        }
        else if (a == '\\') {
            bool signadd = false;
            bool signdel = false;
            string cmp(whole, index, 6);
            for (int i = 0; i < n; i++) {
                if (cmp == nameadd[i] + '{') {
                    Bigthing *nbigthing = new Bigthing;
                    nbigthing->Set(index, true, false);
                    Find.insertBack(nbigthing);
                    index += 5;
                    signadd = true;
                    break;
                }
            }
            for (int i = 0; i < m; i++) {
                if (cmp == namedel[i] + '{') {
                    Bigthing *nbigthing = new Bigthing;
                    nbigthing->Set(index, false, true);
                    Find.insertBack(nbigthing);
                    index += 5;
                    signdel = true;
                    break;
                }
            }
            if ((!signadd) && (!signdel)) {
                string cmpagain(whole, index + 2, 4);//add{
                if (cmpagain == "add{") {
                    Bigthing *nbigthing = new Bigthing;
                    nbigthing->Set(index, false, false);
                    Find.insertBack(nbigthing);
                    index += 5;
                }
                else if (cmpagain == "del{") {
                    Bigthing *nbigthing = new Bigthing;
                    nbigthing->Set(index, false, false);
                    Find.insertBack(nbigthing);
                    index += 5;
                }
                else {
                    while (1) {//escape part
                        index += 1;
                        a=whole[index];
                        if (a != '\\') {
                            break;
                        }
                    }
                }
            }

        }
        else if (a == '{') {
            Bigthing *nbigthing = new Bigthing;
            nbigthing->Set(index, false, false);
            Find.insertBack(nbigthing);
        }
        else if (a == '}') {
            Bigthing *fit = Find.removeBack();
            if (fit->Isadd()) {
                whole.erase(index, 1);
                whole.erase(fit->Position(), 6);
                index -= 7;
            }
            else if (fit->Isdel()) {
                whole.erase(whole.begin() + fit->Position(), whole.begin() + index + 1);
                index-=(index+1-fit->Position());
            }
            delete fit;
        }
        index += 1;
    }
    cout << whole << endl;

    delete[] nameadd;
    delete[] namedel;
}



