#include <iostream>
#include <cstring>
using namespace std;

class A
	{
	public:
	string kolor;
	int liczba;
	A() {cout << "Jestem zwyklym konstruktorem..."<<endl;}
	
	A(int a, string b) : liczba(a), kolor(b)
		{
		cout << "Inicjalizuje zmienne..."<<endl;
		}
	~A()
		{
		cout<<"Jestem zwyklym destruktorem"<<endl;
		}
	A(A&);
	
	};

A::A(A& obiekcik)
	{
	cout<<"Uruchamiam konstruktor kopiujacy..."<<endl;
	kolor=obiekcik.kolor;
	liczba=obiekcik.liczba;
	}

int main()
{
A obiekt(4,"slowo");
A inny = obiekt;
cout << "Pierwszy obiekt: " <<obiekt.liczba << endl;
cout << "Obiekt skopiowany: "<<inny.liczba << endl;

}
