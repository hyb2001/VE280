#include "dlist.h"
#include <iostream>
#include <string>
using namespace std;

enum opStatus {DEL, ADD};

struct status{
    unsigned int position;
    opStatus op;
};

bool findOperator(const string* knownOrder, const string& word, const int& knownNum){
    for (int index = 0; index < knownNum; index++){
        if (knownOrder[index] == word) return true;
    }
    return false;
}

int main(){
    int addNum = 0, delNum = 0;
    cin >> addNum;
    auto* add = new string[addNum];
    for (int num = 0; num < addNum; num++){cin >> add[num];}
    cin >> delNum;
    auto* del = new string[delNum];
    for (int num = 0; num < delNum; num++){cin >> del[num];}
    getchar();
    string subline, line;
    while (!cin.eof() && getline(cin, subline)){
        line.append(subline);
        line.push_back('\n');
        subline.clear();
    }
    unsigned int sz = line.size();
    bool *mark = new bool[sz];
    for (unsigned int num = 0; num < sz; num++) mark[num] = true;
    bool canWrite = true;
    Dlist<status> match;
    status *node;
    for (unsigned int index = 0; index < sz; index++){
        if (canWrite && line[index] == '{' && index >= 5 && findOperator(add, line.substr(index-5, 5), addNum)){
            match.insertBack(new status({index, ADD}));
        }
        else if (canWrite && line[index] == '{' && index >= 5 && findOperator(del, line.substr(index-5, 5), delNum)){
            match.insertBack(new status({index, DEL}));
        }
        else if (canWrite && line[index] == '}' && (index == 0 || line[index-1] != '\\') && !match.isEmpty()){
            node = match.removeBack();
            if (node->op == DEL) {
                for (unsigned int num = node->position - 5; num <= index; num++) mark[num] = false;
            }
            else {
                for (unsigned int num = node->position - 5; num <= node->position; num++) mark[num] = false;
                mark[index] = false;
            }
            delete node;
        }
        else if (line[index] == '%' && (index == 0 || line[index-1] != '\\')) canWrite = false;
        else if (line[index] == '\n') canWrite = true;
    }
    while (!match.isEmpty()){
        node = match.removeBack();
        delete node;
    }
    for (unsigned int num = 0; num < sz; num++) {
        if (mark[num] == true) cout << line[num] << flush;
    }
    delete [] mark;
    delete [] add;
    delete [] del;
    return 0;
}