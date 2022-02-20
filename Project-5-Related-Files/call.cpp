#include "iostream"
#include "dlist.h"
#include "string"

using namespace std;

struct customer{
    string name;
    int startime;
    int stoptime;
    string status;
};

int main(){
    customer *serve,*now,*newcus;
    int cusnum;
    cin>>cusnum;
    auto cus=new Dlist <customer>[4];
    Dlist <customer> cust;
    int round=0,worktime=0;
    for (int i=0; i<cusnum; i++) {
        newcus=new customer;
        if (cin>>newcus->startime>>newcus->name>>newcus->status>>newcus->stoptime) {
            cust.insertBack(newcus);
        }
        //put all the customer into one queue
    }
    bool roundf;
    while (!cust.isEmpty() || !cus[0].isEmpty() || !cus[1].isEmpty() || !cus[2].isEmpty() || !cus[3].isEmpty()){
        cout<<"Starting tick #"<<round<<endl;
        roundf=false;
        while (!roundf && !cust.isEmpty()) {
            //put all the customer into four lists according to round
            now = cust.removeFront();
            if (now->startime == round) {
                cout << "Call from " << now->name << " a " << now->status << " member"<<endl;
                if (now->status == "platinum"){
                   cus[0].insertBack(now);
                }else if (now->status == "gold"){
                    cus[1].insertBack(now);
                }else if (now->status == "silver"){
                    cus[2].insertBack(now);
                } else {
                    cus[3].insertBack(now);
                }
            }else{
                cust.insertFront(now);
                roundf=true;
            }
        }
        if (worktime<=round){
            //find available customer according to their level
            if (!cus[0].isEmpty()){
                serve=cus[0].removeFront();
                cout<<"Answering call from "<<serve->name<<endl;
                worktime=round+serve->stoptime;
                delete serve;
            } else if (!cus[1].isEmpty()){
                serve=cus[1].removeFront();
                cout<<"Answering call from "<<serve->name<<endl;
                worktime=round+serve->stoptime;
                delete serve;
            } else if (!cus[2].isEmpty()){
                serve=cus[2].removeFront();
                cout<<"Answering call from "<<serve->name<<endl;
                worktime=round+serve->stoptime;
                delete serve;
            } else if (!cus[3].isEmpty()){
                serve=cus[3].removeFront();
                cout<<"Answering call from "<<serve->name<<endl;
                worktime=round+serve->stoptime;
                delete serve;
            }
        }
        round++;
    }
    cout<<"Starting tick #"<<round<<endl;
    //final output
    delete []cus;
    return 0;
}