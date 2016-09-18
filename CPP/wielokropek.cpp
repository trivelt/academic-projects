#include <iostream>
#include <cstdarg>
using namespace std;

int suma(int liczba, ...)
	{
	va_list ap;
	va_start( ap, liczba ); // ustawienie ap na pierwszy, jawnie podany, argument
	int sum = 0;
	for (int i = 0; i < liczba; i++ ) 
		{
		sum += va_arg( ap, int ); // odczyt kolejnej zmiennej, sami określamy jej typ!
		}
	va_end( ap ); // porządkowanie stosu, ustawienie ap na 0
	return sum;
	}

void g(int a,...)
	{
	va_list b;
	va_start(b,a);
	cout << "Argumenty funkcji to:"<<endl;
	for(int i=0;i<a;i++)
		{
		cout<<"Argument numer " << (i+1) << " = " << va_arg(b,int) << endl;
		}
	va_end(b);
	}


int main()
{
cout << "Suma wynosi " << suma(3,1,3,5) << endl << endl;
g(5,99,105,0,5,1);
}
