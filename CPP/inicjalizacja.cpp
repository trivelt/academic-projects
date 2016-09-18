/* kompilowac z flaga
-std=c++0x */
#include <iostream>
#include <vector>
using namespace std;

class Para
	{
	public:
	int a,b;
	int tab[2];
	Para(int a,int b):a(a),b(b){}
	Para() : tab{144,169} {} // tablica na liscie inicjalizacyjnej
	};
struct Dane
	{
	int x,y,z;
	};

Para utworzPare()
	{
	return {0,0};
	}

int main()
{
/* inicjalizacja z nawiasami {} */
double liczba{65.24}; // C++11
int a(5); // C++98
int abc = {9};
int tablica[] = {49,51,88,91};
vector<int> wektor {1,2,5};
Para mojapara {4,6}; // konstruktor - nowy styl
Para tablicowa;
cout <<"tablicowa.tab[0] = " << tablicowa.tab[0]<<endl;
cout <<"tablicowa.tab[1] = " << tablicowa.tab[1]<<endl;
Dane publiczne {200}; // reszta inicjalizowana zerami
cout << "X = "<<publiczne.x << ", y = "<<publiczne.y<<", z = "<<publiczne.z<<endl;
}
