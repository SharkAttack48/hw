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
	cout<<"Enter number of employees: ";
	cin>>n;
	cout<<"Enter data (name|experience|salary) of employees: ";
	for (i=0;i<n;i++) cin>>p[i];
	cout<<"\n";
	for (i=0;i<n;i++) cout<<p[i];
	cout<<"\n";
	bool f=1;
	for (i=0;i<n && f;i++)
		if(p[i].getexp()<10)
		{		
			s=i;
			f=0;
		}
	unsigned maxsl=p[s].getsal();
	char*maxslfio;
	maxslfio=new char[strlen(p[s].getfio())+1];
	strcpy(maxslfio,p[s].getfio());
	for (i=s+1;i<n;i++)
		if ((p[i].getsal()>maxsl) && (p[i].getexp()<10))
		{
			maxsl=p[i].getsal();
			strcpy(maxslfio,p[i].getfio());
		}
	if (!f) cout<<"man with experience <10 and max salary: "<<maxslfio;
	else cout<<"all employees 10+ experience";
	cout<<"\n";
	p[n+1]=p[2];
	cout<<"operator '=' test "<< p[n+1];
}
