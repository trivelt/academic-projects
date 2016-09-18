#include <iostream>
using namespace std;

/***********************
Zagniezdzanie w klasach
***********************/
class Samochod
	{
	public:
	class Silnik
		{
		public:
		void napraw();
		};
	class Kierownica
		{
		public:
		void obracaj();
		};
	};
void Samochod::Kierownica::obracaj() { cout << "Obracam..."<<endl; }
void Samochod::Silnik::napraw() { cout << "Naprawiam..."<<endl; }

/***********************
Zagniezdzanie klas w funkcjach
***********************/

int funkcja()
	{
	class A
		{
		public:
		int a;
		};
	A a;
	a.a=2;
	cout<<a.a<<endl;
	for (int i=0;i<3;i++)
		{
		class A // inna klasa, zaslanianie nazw 
			{
			public:
			double b;
			};
		A b;
		b.b=i;
		cout<<"b="<<b.b<<endl;
		}
	}

int main()
{
Samochod::Silnik mojsilnik;
mojsilnik.napraw();
funkcja();
}
