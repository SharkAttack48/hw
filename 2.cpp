#include <iostream>
#include <cstring>
using namespace std;
class people
{
	private:
		char* fio;
		unsigned exp, sal;
	public:
		people (){fio=NULL;}
		people (char*,unsigned,unsigned);
		~people (){delete [] fio;}
		char* getfio(){return fio;}
		unsigned getexp(){return exp;}
		unsigned getsal(){return sal;}
		void print();
		people(const people&);
};

people::people(char* afio, unsigned aexp, unsigned asal)
{
	int n;
	n=strlen(afio);
	fio=new char[n+1];
	strcpy(fio,afio);
	exp=aexp;
	sal=asal;
}

people::people(const people&p)
{
	int n;
	n=strlen(p.fio);
	fio=new char[n+1];
	strcpy(fio,p.fio);
	exp=p.exp;
	sal=p.sal;
}

void people::print()
{
	cout<<"Name:"<<fio<<" exp:"<<exp<<" sal:"<<sal;
	cout<<'\n';
}

int main()
{
	people*p[10];
	char name[30];
	int i,n,s;
	unsigned sl,xp;
	cin>>n;
	for (i=0;i<n;i++)
	{
		cin >>name >>xp >>sl;
		p[i]=new people(name,xp,sl);
	}
	cout<<'\n';
	for (i=0;i<n;i++) p[i]->print();
	cout<<'\n';
	unsigned maxsl=p[0]->getsal();
	char*maxslfio;
	maxslfio=new char[strlen(p[0]->getfio())+1];
	strcpy(maxslfio,p[0]->getfio());
	for (i=1;i<n;i++)
		if ((p[i]->getsal()>maxsl) && (p[i]->getexp()<10))
		{
			maxsl=p[i]->getsal();
			strcpy(maxslfio,p[i]->getfio());
		}
	cout<<"man with exp < 10 & maxsl:"<<maxslfio;
	cout<<'\n';
	for (i=0;i<n;i++) delete p[i];
}
