#include <iostream>
using namespace std;

class A {
	public:
	virtual void getMe() { cout << "Jestem A\n"; }
	virtual void fun() {cout << "Wirtualna funkcja A\n";}
	};
class B : public A
	{
	private:
	void fun() { cout << "Wirtualna funkcja B\n";}
	public:
	void getMe() { cout << "Jestem B\n";}
	};
class C : public B 
	{
	public:
	virtual void getMe() { cout << "Jestem C\n"; } // "virtual" nie jest konieczne
	};

class Abstrakcyjna
	{
	public:
	virtual void funkcja() = 0;
	};
class Normalna : public Abstrakcyjna
	{
	public:
	virtual void funkcja() {cout << "Zaimplementowana"<<endl;}
	};

int main()
{
B b;
C c;
A *ptrA = &b;
B *ptrB = &b;
A &refA = c;
A a = b;
ptrA->getMe();
refA.getMe();
a.getMe();

(*ptrA).fun();
//(*ptrB).fun(); BLAD! ‘virtual void B::fun()’ is private
// Abstrakcyjna d; BLAD! nie mozna tworzyc obiektow klasy abstrakcyjnej
Normalna rzecz;
rzecz.funkcja();
}
