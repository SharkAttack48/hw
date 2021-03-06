#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

class people
{
	protected:
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
		void print(){cout<<"Name:"<<fio<<" exp:"<<exp<<" sal:"<<sal;}
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
	s<<p.fio<<" "<<p.exp<<" "<<p.sal;
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

class g_people:public people
{
	char* gender;
	public:
		g_people():people(){gender=NULL;}
		g_people(const g_people&);
		g_people(const g_people&,char*);
		g_people(const people&,char*);
		g_people(char*,unsigned,unsigned,char*);
		~g_people(){delete [] gender;}
		char* getgender(){return gender;}
		void print(){people::print();cout<<" "<<gender;}
		g_people& operator=(const g_people&);
		friend ostream& operator<<(ostream&,const g_people&);
		friend istream& operator>>(istream&,g_people&);
};

g_people::g_people(char*afio,unsigned aexp,unsigned asal,char*agender):people(afio,aexp,asal)
{
	gender=new char[strlen(agender)+1];
	strcpy(gender,agender);
}

g_people::g_people(const people& p,char* agender):people(p)
{
	gender=new char[strlen(agender)+1];
	strcpy(gender,agender);
}

g_people::g_people(const g_people& p,char* agender):people(p)
{
	gender=new char[strlen(agender)+1];
	strcpy(gender,agender);
}

ostream&operator<<(ostream& s,const g_people& c)
{
	s<<people(c)<<" "<<c.gender<<"\n";
	return s;
}

istream&operator>>(istream& s,g_people& c)
{
	char buf[100];
	people x;
	c.~g_people();
	s>>x>>buf;
	c=g_people(x,buf);
	return s;
}

g_people&g_people::operator=(const g_people& p)
{
	if (&p!=this)
	{
		this->~g_people();
		fio=new char[strlen(p.fio)+1];strcpy(fio,p.fio);
		gender=new char[strlen(p.gender)+1];strcpy(gender,p.gender);
		exp=p.exp;sal=p.sal;		
	}
	return *this;
}

int main()
{
	g_people p[10];
	char name[30];
	int i,n,s;
	unsigned sl,xp;
	char t[]="w";
	cout<<"Enter number of employees: ";
	cin>>n;
	cout<<"Enter data (name|exp|sal|gen) of employees: ";
	for (i=0;i<n;i++) cin>>p[i];
	cout<<"\n";
	for (i=0;i<n;i++) cout<<p[i];
	cout<<"\n";
	bool f=1;
	for (i=0;i<n && f;i++)
		if((!strcmp(p[i].getgender(),t))&&(p[i].getexp()<10))
		{		
			s=i;
			f=0;
		}
	unsigned maxsl=p[s].getsal();
	char*maxslfio;
	maxslfio=new char[strlen(p[s].getfio())+1];
	strcpy(maxslfio,p[s].getfio());
	for (i=s+1;i<n;i++)
		if ((p[i].getsal()>maxsl)&&(p[i].getexp()<10)&&(!strcmp(p[i].getgender(),t)))
		{
			maxsl=p[i].getsal();
			strcpy(maxslfio,p[i].getfio());
		}
	if (!f) cout<<"woman with experience <10 and max salary: "<<maxslfio;
	else cout<<"all employees 10+ experience";	
	cout<<"\n";
	p[n+1]=p[1];
	cout<<"operator '=' test "<< p[n+1];
}
