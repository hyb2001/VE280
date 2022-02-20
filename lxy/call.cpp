#include<iostream>
#include<string>
#include<cstring>
#include "dlist.h"
using namespace std;

const int MAX_CLIENT=3000;

struct client
{
	string name,status;
	int time; //defult 0, add 1, del -1
	int duration;
};

int main()
{
	Dlist<client> regular,silver,gold,platinum;
	string name,status;
	client c[MAX_CLIENT];
	client *newClient;
	int isBusy=0;
	int n,t,d,time,current;
	int print;

	cin>>n;
	time=0;current=0;
	cout<<"Starting tick #0"<<endl;
	for (int i=0;i<n;i++) 
	{	
		cin>>t>>name>>status>>d;
		c[i].name=name;
		c[i].time=t;
		c[i].duration=d;
		c[i].status=status;
	}
	//for (int i=0;i<n;i++) cout<<c[i].name<<" "<<c[i].time<<" "<<c[i].duration<<" "<<c[i].status<<endl;
	while (current<n)
	{
		if (isBusy<time || time==c[current].time)
		do
		{
			client *node=new client;
			node->name=c[current].name;
			node->time=c[current].time;
			node->duration=c[current].duration;
			node->status=c[current].status;
			//cout<<node->name<<" "<<node->time<<" "<<node->duration<<" "<<node->status<<endl;
			if (node->status=="regular") regular.insertBack(node);
			else if (node->status=="silver") silver.insertBack(node);
			else if (node->status=="gold") gold.insertBack(node);
			else platinum.insertBack(node);
			while (time<node->time) 
			{
				time++;
				cout<<"Starting tick #"<<time<<endl;
			}
			cout<<"Call from "<<c[current].name<<" a "<<c[current].status<<" member"<<endl;
			current++;
		}
		while (current<n && c[current].time==c[current-1].time);
		if (isBusy>time)
		{
			//cout<<isBusy<<" "<<time<<endl;
			time++;
			cout<<"Starting tick #"<<time<<endl;
			continue;
		}
		if (!platinum.isEmpty())
		{
			newClient=platinum.removeFront();
			isBusy=time+newClient->duration;
			cout<<"Answering call from "<<newClient->name<<endl;
			delete newClient;
		}
		else if (!gold.isEmpty())
		{
			newClient=gold.removeFront();
			isBusy=time+newClient->duration;
			cout<<"Answering call from "<<newClient->name<<endl;
			delete newClient;
		}
		else if (!silver.isEmpty())
		{
			newClient=silver.removeFront();
			isBusy=time+newClient->duration;
			cout<<"Answering call from "<<newClient->name<<endl;
			delete newClient;
		}
		else if (!regular.isEmpty())
		{
			newClient=regular.removeFront();
			isBusy=time+newClient->duration;
			cout<<"Answering call from "<<newClient->name<<endl;
			delete newClient;
		}
	}
	while (isBusy>time)
	{
		time++;
		cout<<"Starting tick #"<<time<<endl;
	}
	while (!platinum.isEmpty())
	{
		//cout<<"P"<<endl;
		newClient=platinum.removeFront();
		isBusy=time+newClient->duration;
		cout<<"Answering call from "<<newClient->name<<endl;
		while (isBusy>time) 
		{
			time++;
			cout<<"Starting tick #"<<time<<endl;
		}
		delete newClient;
	}
	while (!gold.isEmpty())
	{
		//cout<<"G"<<endl;
		newClient=gold.removeFront();
		isBusy=time+newClient->duration;
		cout<<"Answering call from "<<newClient->name<<endl;
		while (isBusy>time) 
		{
			time++;
			cout<<"Starting tick #"<<time<<endl;
		}
		delete newClient;
	}
	while (!silver.isEmpty())
	{
		//cout<<"S"<<endl;
		newClient=silver.removeFront();
		isBusy=time+newClient->duration;
		cout<<"Answering call from "<<newClient->name<<endl;
		while (isBusy>time) 
		{
			time++;
			cout<<"Starting tick #"<<time<<endl;
		}
		delete newClient;
	}
	while (!regular.isEmpty())
	{
		//cout<<"R"<<endl;
		newClient=regular.removeFront();
		isBusy=time+newClient->duration;
		cout<<"Answering call from "<<newClient->name<<endl;
		while (isBusy>time) 
		{
			time++;
			cout<<"Starting tick #"<<time<<endl;
		}
		delete newClient;
	}
	return 0;
}