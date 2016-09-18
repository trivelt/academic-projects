#include <iostream>
using namespace std;

class A
	{
	private:
	int skladnik;
	protected:
	char znak;
	public:
	static int statyczna;
	float liczba;
	void fun() {cout << "Funkcja fun() obiektu klasy A" << endl;}
	int odczytaj(){return skladnik;}
	void zapisz(int x){skladnik=x;}
	};

class B : public A
	{
	public:
	// int czytaj(){return skladnik;} NIE MOZNA
	static int statyczna;
	double liczba;
	void fun() {cout << "Funkcja fun() obiektu klasy B" << endl;}
	};

int A::statyczna=11;
int B::statyczna=12;

int main()
{
B b;
A a;
a.zapisz(55);
cout << "Skladnik A: " << a.odczytaj() << endl;
b.zapisz(4);
cout << "Skladnik B: " << b.odczytaj() << endl;
b.fun();
b.A::fun();
cout << b.statyczna << endl;
}
