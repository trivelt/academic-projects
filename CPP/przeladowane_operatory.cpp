#include <iostream>
using namespace std;

class A
	{
	int i;
	public:
	A(int n=0) : i(n) {} // konstruktor
	int pokaz(){return i;}
	void zmien(int a){i=a;}
	/* operatory jednoargumentowe */
	friend const A operator-(const A& a); // jako funkcja globalna
	bool operator!() const { return !i; } // jako skladowa klasy
	const A& operator++() {i++; return *this;}
	/* operatory dwuargumentowe */
	friend const A operator+(const A&, const A&); // funkcja zaprzyjazniona
	A& operator=(const A&b)
		{
		if(this==&b) return *this; // przypisanie do samego siebie
		i=b.i;
		return *this;
		}
	};

const A operator-(const A& a)
	{
	return A(-a.i);
	}

const A operator+(const A& a, const A& b)
	{
	A temp(a.i+b.i); // obiekt tymczasowy
	return temp;
	}

int main()
{
A test(5);
cout << "test "<<test.pokaz()<<endl;
test=-test;
cout << "test "<<test.pokaz()<<endl;
cout << "test "<< !test <<endl;
A obiekt(53);
A suma = obiekt+test;
cout << "Suma = " << suma.pokaz() << endl;
test=suma;
++test;
cout << "test "<<test.pokaz()<<endl;
}
