#include <iostream>
#include <iomanip>
#define T 4

using namespace std;

class vektor
{
	double*a;
	int n;
	public:
		vektor(int an){a=new double [n=an];}
		~vektor(){delete []a;}
		double& operator[](int k){return a[k];}
		vektor operator*(const double&);
		friend double operator*(const vektor&,const vektor&);
};

double operator*(const vektor& u,const vektor& v)
{
	double product=0;
	for (int i=0;i<u.n;i++)
		product+=u.a[i]*v.a[i];
	return product;
}

vektor vektor::operator*(const double& c)
{
	vektor product=*this;
	for(int i=0;i<n;i++)
		product[i]*=c;
	return product;
}

int main()
{
	vektor p(T),q(T),r(T),s(T);
	double n;
	cout<<"Enter P coordinates: ";
	for(int i=0;i<T;i++) cin>>p[i];
	cout<<"Enter Q coordinates: ";
	for(int i=0;i<T;i++) cin>>q[i];
	cout<<"P*Q="<<p*q<<"\n";
	cout<<"Enter R coordinates: ";
	for(int i=0;i<T;i++) cin>>r[i];
	cout<<"Enter n: "; cin>>n;
	p=r*n;
	cout<<"R*n=( ";
	for(int i=0;i<T;i++) cout<<p[i]<<" ";
	cout<<")\n";
}
