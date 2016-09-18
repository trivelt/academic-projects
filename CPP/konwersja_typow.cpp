/* uzycie konstruktora konwersji i operatora konwersji */
#include <iostream>
using namespace std;

class B
	{
	public:
	double a, b;
	B(int, int);
	};

class A
	{
	public:
	int m,n;
	A(int x,int y): m(x), n(y) {};
	operator B() const  // operator konwersji
		{
		return B(m,n);
		}
	};

class C
	{
	public:
	float zmienna;
	int liczba;
	C() {cout << "Nic nierobiacy konstruktor"<<endl;}
	C(const B&); // konstruktor konwersji
	};

C::C(const B& obiekt)
	{
	zmienna=(float)obiekt.a;
	liczba=(int)obiekt.b;
	}

B::B(int liczba1, int liczba2)
	{
	a=(double)liczba1;
	b=(double)liczba2;
	}

void fun(B obiekt)
	{
	cout << "Otrzymalem obiekt B z liczbami " << obiekt.a<<" i "<<obiekt.b<<endl;
	}

void fun2(C obiekt)
	{
	cout << "Otrzymalem obiekt C z liczbami " << obiekt.zmienna<<" i "<<obiekt.liczba<<endl;
	}

int main()
{
A costam(19,50);
fun(costam);
B testowy(15,18);
fun2(testowy);
}
