#include <iostream>
#include <cstring>

using namespace std;

class people
{
	private:
		char* fio;
		unsigned exp, sal;
	public:
		people(){fio=NULL;}
		people(char*,unsigned,unsigned);
		~people(){delete [] fio;}
		char* getfio(){return fio;}
		unsigned getexp(){return exp;}
		unsigned getsal(){return sal;}
		void print();
		people(const people&);
};

people::people(char* afio, unsigned aexp, unsigned asal)
{
	fio=new char[strlen(afio)+1];
	strcpy(fio,afio);
	exp=aexp;sal=asal;
}

people::people(const people&p)
{
	fio=new char[strlen(p.fio)+1];
	strcpy(fio,p.fio);
	exp=p.exp;sal=p.sal;
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
	cout<<"Enter number of employers: ";
	cin>>n;
	cout<<"Enter data (name|experience|salary) of employers: ";
	for (i=0;i<n;i++)
	{
		cin >>name >>xp >>sl;
		p[i]=new people(name,xp,sl);
	}
	cout<<"\n";
	for (i=0;i<n;i++) p[i]->print();
	cout<<"\n";
	for (i=0;i<n;i++)
		if(p[i]->getexp()<10)
		{		
			s=i;
			break;
		}
	unsigned maxsl=p[s]->getsal();
	char*maxslfio;
	maxslfio=new char[strlen(p[s]->getfio())+1];
	strcpy(maxslfio,p[s]->getfio());
	for (i=s+1;i<n;i++)
		if ((p[i]->getsal()>maxsl) && (p[i]->getexp()<10))
		{
			maxsl=p[i]->getsal();
			strcpy(maxslfio,p[i]->getfio());
		}
	cout<<"man with experince <10 and max salary: "<<maxslfio;
	cout<<'\n';
	for (i=0;i<n;i++) delete p[i];
}
