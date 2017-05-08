#include <iostream>

using namespace std;

struct node{
	int inf;
	node *n,*p;
	node(int x){
		inf=x;
		n=NULL;
		p=NULL;
	}
};

class dll
{
	node *beg;
	node *end;
	int length;
	public:
		dll(){beg=NULL;end=NULL;length=0;}
		dll(const dll&);
		~dll(){destroy();}
		bool empty(){return (beg==NULL && end==NULL);}
		void destroy();
		void addbeg(int x);
		void addend(int x);
		void print();
		void reverse();
		friend ostream& operator<<(ostream& output,const dll& list);
		friend istream& operator>>(istream& input,dll& list);
		dll& operator=(const dll&);
		void setlength(int x){length=x;}
		int getbeg(){return this->beg->inf;}
		int getend(){return this->end->inf;}
		int getlength(){return length;}
};

dll::dll(const dll&p){
	node *newnode=p.beg;
	node **tail=&beg;
	while(newnode){
		*tail=new node(newnode->inf);
		tail=&(*tail)->n;
		newnode=newnode->n;
	}
}

void dll::destroy()
{
	node *temp1=end;
	while(temp1!=NULL){
		node *temp2=temp1;
		temp1=temp1->p;
		delete temp2;
	}
	beg=NULL;
	end=NULL;
	length=0;
}

void dll::addbeg(int x)
{
	node *temp=new node(x);
	if(beg==NULL){
		beg=temp;
		end=temp;
	}
	else{
		beg->p=temp;
		temp->n=beg;
		beg=temp;
	}
}

void dll::addend(int x)
{
	node *temp=new node(x);
        if(end==NULL){
		beg=temp;
		end=temp;
	}
	else{
		end->n=temp;
		temp->p=end;
		end=temp;
	}
}

void dll::print()
{
	node *temp=beg;
	while(temp!=NULL){
		cout<<temp->inf<<(temp->n?", ":"\n");
		temp=temp->n;
	}
}

void dll::reverse()
{
	node *p1, *p2;
	p1=this->beg;
	p2=p1->n;
	p1->n=NULL;
	p1->p=p2;
	while (p2){
		p2->p=p2->n;
		p2->n=p1;
		p1=p2;
		p2=p2->p;
	}
	this->beg=p1;
}

istream&operator>>(istream& input,dll& list){
	if (list.length!=0){
		cout<<"	Enter elements: ";
		int inf;
		for(int i=0;i<list.length;i++){
			input>>inf;
			list.addend(inf);
		}
		return input;
	}
	else cout<<"	Error, the number of elements must be >0\n\n";
}

ostream& operator<<(ostream& output,const dll& list){
	node *p=list.beg;
	while(p){
	output<<p->inf<<(p->n?", ":"\n");
	p=p->n;
	}
	return output;
}

dll&dll::operator=(const dll&p){
	if (&p!=this){
		this->~dll();
		node *newnode=p.beg;
		node **tail=&beg;
		while(newnode){
			*tail=new node(newnode->inf);
			tail=&(*tail)->n;
			newnode=newnode->n;
		}
	}
	return *this;
}

int main()
{
	dll list,list2;
	int n;
	cout<<"	Add elements to the beginning: ";
	for(int i=1;i<4;i++) list.addbeg(i*3.14);
	list.print();

	cout<<"	Add elements to the end: ";
	for(int i=1;i<4;i++) list.addend(i*2.71);
	list.print();

	cout<<"	operator<< test: ";
	cout<<list;

	cout<<"	Removing current list...\n";
	list.destroy();
	cout<<(list.empty()?"	Remove succesfull.\n":"	Error 404\n\n");

	cout<<"	operator>> test:\n";
	cout<<"	Create new list.\n	Enter the number of elements: ";
	cin>>n;
	list2.setlength(n);
	cout<<"	setlength test: "<<list2.getlength()<<"\n";
	cin>>list2;

	cout<<"	get methods test: "<<list2.getbeg()<<" - first element, "<<list2.getend()<<" - last element"<<"\n";

	cout<<"	operator= test: ";
	list=list2;
	list.print();
	cout<<(list.empty()?"	Error 505\n\n":"	Overloading of assignment operator test succesfully completed\n");

	cout<<"	reverse function test: ";
	list.reverse();
	list.print();
}
