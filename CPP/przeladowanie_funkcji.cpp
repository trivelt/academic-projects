#include <iostream>
using namespace std;

void przeladowana(int a)
	{
	cout << "Funkcja z argumentem "<<a<<endl;
	}
// int przeladowana(int); TAK NIE MOZNA
void przeladowana(int a, char b)
	{
	cout <<"[PIERWSZA] Funkcja z argumentem "<<a<<" i znakiem "<<b<<endl;
	}
void przeladowana(char b, int a)
	{
	cout <<"[DRUGA] Funkcja z argumentem "<<a<<" i znakiem "<<b<<endl;
	}
void przeladowana(int a, int b)
	{
	cout <<"Funkcja z argumentami "<<a<<" oraz "<<b<<endl;
	}

int tablicowa(int tab[], int arg)
	{
	cout <<"Argument to "<< arg << endl;
	}

/* TEGO NIE MOZEMY JUZ ZDEFINIOWAC
int tablicowa(int* wsk, int arg)
	{
	cout<<"Lorem ipsum"<<endl;
	}
*/

int main()
{
przeladowana(5,'1');
przeladowana('5',1);
int tab[5]={0};
tablicowa(tab,21);
int tablicowa(int* tab,int = 0);
tablicowa(tab);
}


