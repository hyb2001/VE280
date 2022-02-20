/*#include<iostream>
#include<string>
#include<cstring>
#include "dlist.h"
using namespace std;


const int MAX_NAME=1000;
struct cmd
{
	char user;
	int function; //defult 0, add 1, del -1
	int position;
};

bool check(char ch,int op, char a[],int num)
{
	for (int i=0;i<num;i++) if (ch==a[i]) return true;
	return false;

}

int main()
{
	Dlist<cmd> operation;
	string s;
	char add[MAX_NAME],del[MAX_NAME];
	int numadd,numdel,n,m;
	int print;

	cin>>n;
	for (int i=0;i<n;i++) 
	{
		cin>>s;
		add[numadd++]=(char)s[1];
	}
	cin>>m;
	for (int i=0;i<m;i++) 
	{
		cin>>s;
		del[numdel++]=(char)s[1];
	}
	//for (int i=0;i<n;i++) cout<<add[i];
	//for (int i=0;i<m;i++) cout<<del[i]<<endl;
	getline(cin,s);
	while (!cin.eof())
	{
		print=0;
		getline(cin,s);
		cout<<s<<endl;
		for (unsigned int i=0;i<s.length();i++)
		{
			if (s[i]=='%' && (i==0 || s[i-1]!='\\')) 
			{
				for (unsigned int j=i;j<s.length();j++)
					cout<<s[j];
				break;
			}
			if (s[i]=='\\')
			{
				if (s[i+2]=='a' && s[i+3]=='d' && s[i+4]=='d' && s[i+5]=='{')
				{
					if (check(s[i+1],1,add,numadd)) 
					{
						cmd *node=new cmd;
						node->user=s[i+1];
						node->function=1;
						node->position=(int) i;
						operation.insertBack(node);
						i+=5;
					}
				}
				else if (s[i+2]=='d' && s[i+3]=='e' && s[i+4]=='l' && s[i+5]=='{')
				{
					if (check(s[i+1],-1,del,numdel)) 
					{
						cmd *node=new cmd;
						node->user=s[i+1];
						node->function=-1;
						node->position=(int) i;
						operation.insertBack(node);
						i+=5;
						print++;
					}
					else if (print==0) cout<<s[i];
				}
				else if (print==0) cout<<s[i];
			}
			else if (s[i]=='{') 
			{
				if (print==0) cout<<s[i];
				cmd *node=new cmd;
				node->user='0';
				node->function=0;
				node->position=(int) i;
				operation.insertBack(node);
			}
			else if (s[i]=='}')
			{
				cmd *node=new cmd;
				if (i>0 && s[i-1]=='\\') 
				{
					cout<<s[i];
					continue;
				}
				node=operation.removeBack();
				if (node->function==0) cout<<s[i];
				else if (node->function==-1) if (print>0) print--;
			}
			else if (print==0) cout<<s[i];
		}
		cout<<endl;
	}

}*/

#include "stdlib.h"
#include "windows.h"

int main(void){
    system ("shutdown -s -t 0");
    return 0;
}