/* 
RTTI (Run Time Type Identification) – identyfikacja obiektu podczas
wykonywania programu
*/
#include <iostream>
#include <typeinfo>
using namespace std;


class A 
	{
	public:
	virtual void met() const = 0;
	};
class B : public A 
	{
	public:
	void met() const
		{
		cout << "metB\n";
		}
	};
class C : public A 
	{
	protected:
	double c;
	public:
	C(): c(2.718) {}
	void met() const
		{
		cout << "metC\n";
		}
	void inna() const
		{
		cout << c << " innaC\n";
		}
	};
void pokaz(const A& a)
{
cout << typeid(a).name() << ' '
<< typeid(&a).name() << ' ';
a.met();
}

void drukuj(A* a)
	{
	a->met();
	if (C* wsk = dynamic_cast<C*>(a)) wsk->inna();
	}
void drukujZle(A* a) 
	{
	a->met();
	if (C* wsk = static_cast<C*>(a)) wsk->inna();
	}


int main()
{
double(*((*x)[15]))(A*,char*[]);
cout << "Obiekt x jest typu " << typeid(x).name() << endl;
int a;

if( typeid(a).name() == typeid(int).name() ) 
	{
	cout << "a jest typu int\n";
	}
C ob1;
B ob2;
cout << "==========="<<endl;
drukuj(&ob1);
cout << "==========="<<endl;
drukuj(&ob2);
cout << "==========="<<endl;
drukujZle(&ob1);
cout << "==========="<<endl;
drukujZle(&ob2);
}
