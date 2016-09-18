#include <iostream>
using namespace std;

class T
	{
	public:
	int a,b,c;
	T() {}
	T(int x,int y,int z):a(x),b(y),c(z) {}
	double tab[15];
	};

int main()
{
T obiekt(19,219,373);
int T::*wsk; // wskaznik na inty w klasie T
T* wskT; // wskaznik na obiekty T
wsk=&T::a;
wskT= &obiekt;
(*wskT).a=21;
cout << "Wskazuje na: " << wskT->*wsk << endl;
wsk=&T::c;
cout << "Wskazuje na: " << obiekt.*wsk << endl;
double (T::*wskTab)[15]; // wskaznik do tablicy
wskTab=&T::tab; // ampersand konieczny
int T::*(tabWsk)[3] = {&T::a, &T::b, &T::c}; // tablica wskaznikow na skladowe int
cout << "===== W pętli ==== "<<endl;
for(int i=0;i<3;i++)
	{
	cout << "tab["<<i<<"] = "<< obiekt.*(tabWsk[i]) << endl;
	}
}
