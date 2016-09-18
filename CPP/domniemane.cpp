#include <iostream>
using namespace std;

char zwieloma(int x=5,...); // OK
// char innafunkcja(int x=5,int y); BLAD!

void fun1(int a, int b, int c = 8)
	{
	cout << "a="<<a<<endl;
	cout << "b="<<b<<endl;
	cout << "c="<<c<<endl;
	}

int main()
{
fun1(1,2);
void fun1(int a,int = 3,int c=18);
cout << "===Kolejne wywolanie==="<<endl;
fun1(1);
void fun1(int=0, int, int a);
cout << "===Kolejne wywolanie==="<<endl;
fun1();
}
