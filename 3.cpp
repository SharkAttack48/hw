#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
class people
{
	private:
		char* fio;
		unsigned exp, sal;
	public:
		people(){fio=NULL;}
		people(const people&);
		people(char*,unsigned,unsigned);
		~people(){delete [] fio;}
		people& operator=(const people&);
		friend ostream& operator<<(ostream&,const people&);
		friend istream& operator>>(istream&,people&);
		char* getfio(){return fio;}
		unsigned getexp(){return exp;}
		unsigned getsal(){return sal;}
};

people::people(const people&p)
{
	fio=new char[strlen(p.fio)+1];
	strcpy(fio,p.fio);
	exp=p.exp;sal=p.sal;
}

people::people(char* afio, unsigned aexp, unsigned asal)
{
	fio=new char[strlen(afio)+1];
	strcpy(fio,afio);
	exp=aexp;sal=asal;
}

people& people::operator=(const people& p)
{
	if (this!=&p)
	{
		delete[]fio;
		fio=new char[strlen(p.fio)+1];
		strcpy(fio,p.fio);
		exp=p.exp;sal=p.sal;
	}
	return *this;
}

ostream& operator<<(ostream& s,const people& p)
{
	s<<p.fio<<" "<<p.exp<<" "<<p.sal<<"\n";
	return s;
}

istream& operator>>(istream& s,people& p)
{
	char buf[100];
	s>>buf>>p.exp>>p.sal;
	delete[]p.fio;
	p.fio=new char[strlen(buf)+1];
	strcpy(p.fio,buf);
	return s;
}

int main()
{
	people p[10];
	char name[30];
	int i,n,s;
	unsigned sl,xp;
	cin>>n;
	for (i=0;i<n;i++) cin>>p[i];
	cout<<'\n';
	for (i=0;i<n;i++) cout<<p[i];
	cout<<'\n';
	unsigned maxsl=p[0].getsal();
	char*maxslfio;
	maxslfio=new char[strlen(p[0].getfio())+1];
	strcpy(maxslfio,p[0].getfio());
	for (i=1;i<n;i++)
		if ((p[i].getsal()>maxsl) && (p[i].getexp()<10))
		{
			maxsl=p[i].getsal();
			strcpy(maxslfio,p[i].getfio());
		}
	cout<<"man with exp < 10 & maxsl:"<<maxslfio;
	cout<<'\n';
	p[n+1]=p[2];
	cout<<"operator= test "<<p[n+1];
}
