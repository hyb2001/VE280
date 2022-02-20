//
// Created by 肖斯琪 on 2020/12/4.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
using namespace std;

class Bigthing{
    int tick;
    string name;
    string level;
    int duration;
public:
    int Duration(){
        return duration;
    }
    string Name(){
        return name;
    }
    string Level(){
        return level;
    }
    int Tick(){
        return tick;
    }
    Bigthing(){
        tick=duration=0;
        name=level="";
    }
    ~Bigthing(){}
    void Set(int tick,string name,string level,int duration){
        this->tick=tick;
        this->level=level;
        this->name=name;
        this->duration=duration;
    }

};

int pickOne(int currentduration,Dlist<Bigthing> &Platinum, Dlist<Bigthing> &Gold, Dlist<Bigthing> &Silver, Dlist<Bigthing> &Regular){
    if (!Platinum.isEmpty()) {
        Bigthing *person;
        person = Platinum.removeFront();
        cout << "Answering call from " << person->Name() << endl;
        currentduration = person->Duration();
        delete person;
    }
    else if (!Gold.isEmpty()) {
        Bigthing *person;
        person = Gold.removeFront();
        cout << "Answering call from " << person->Name() << endl;
        currentduration = person->Duration();
        delete person;
    }
        else if (!Silver.isEmpty()) {
        Bigthing *person;
        person = Silver.removeFront();
        cout << "Answering call from " << person->Name() << endl;
        currentduration = person->Duration();
        delete person;
    }
        else if (!Regular.isEmpty()) {
        Bigthing *person;
        person = Regular.removeFront();
        cout << "Answering call from " << person->Name() << endl;
        currentduration = person->Duration();
        delete person;
    }
        return currentduration;
    }



int main() {
    int num;//event number
    cin >> num;
    string useless;
    getline(cin, useless);
    int second = 0;
    int tick;
    string name;
    string level;
    int duration;
    int currentduration = 0;
    Dlist<Bigthing> Whole;
    Dlist<Bigthing> Platinum;
    Dlist<Bigthing> Gold;
    Dlist<Bigthing> Silver;
    Dlist<Bigthing> Regular;
    for (int i = 0; i < num; i++) {
        Bigthing *save = new Bigthing;
        cin >> tick >> name >> level >> duration;
        save->Set(tick, name, level, duration);
        Whole.insertBack(save);
    }


    while (!Whole.isEmpty()||!Platinum.isEmpty()||!Gold.isEmpty()||!Silver.isEmpty()||!Regular.isEmpty()) {
        if(second>=10){
            break;
        }
        cout << "Starting tick #" << second << endl;
        while (1) {
            Bigthing *Try;
            if (!Whole.isEmpty()) {
                Try = Whole.removeFront();
                if (Try->Tick() == second) {
                    if (Try->Level() == "platinum") {
                        Platinum.insertBack(Try);
                    }
                    else if (Try->Level() == "gold") {
                        Gold.insertBack(Try);
                       // cout<<"here"<<endl;
                    }
                    else if (Try->Level() == "silver") {
                        Silver.insertBack(Try);
                    }
                    else if (Try->Level() == "regular") {
                        Regular.insertBack(Try);
                    }
                    cout << "Call from " << Try->Name() << " a " << Try->Level() << " member" << endl;
                }
                else {
                    Whole.insertFront(Try);
                    break;
                }
            }
            else {
                break;
            }
        }
        if(currentduration==0) {
           currentduration=pickOne(0,Platinum,Gold,Silver,Regular);
        }
        second += 1;
        if(currentduration>=1){
            currentduration-=1;
        }
    }
    cout << "Starting tick #" << second << endl;
}






//if (!Platinum.isEmpty()) {
//Bigthing *person;
//person = Platinum.removeFront();
//cout << "Answering call from " << person->Name() << endl;
//currentduration = person->Duration();
//delete person;
//}
//else if (!Gold.isEmpty()) {
//Bigthing *person;
//person = Gold.removeFront();
//cout << "Answering call from " << person->Name() << endl;
//currentduration = person->Duration();
//delete person;
//}
//else if (!Silver.isEmpty()) {
//Bigthing *person;
//person = Silver.removeFront();
//cout << "Answering call from " << person->Name() << endl;
//currentduration = person->Duration();
//delete person;
//}
//else if (!Regular.isEmpty()) {
//Bigthing *person;
//person = Regular.removeFront();
//cout << "Answering call from " << person->Name() << endl;
//currentduration = person->Duration();
//delete person;
//}







