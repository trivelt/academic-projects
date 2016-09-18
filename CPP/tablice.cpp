/* tablice */
#include <cstring> // dla: memset()
#include <iostream>
using namespace std;

void tablicowa(int tab[][4], int liczba) // skrajnie lewy indeks nie musi byc znany
	{
	for(int i=0;i<liczba;i++)
		{
		for(int j=0;j<4;j++)
			{
			cout << "tab["<<i<<"]"<<"["<<j<<"] = "<<tab[i][j]<<endl;
			}
		}
	}

int main()
{
const int stale[3] = {15,19,55}; // inicjalizacja konieczna
double zmienne[5] = {1.0, 2.5};
double zw[5];
cout << "zmienne[2]: " << zmienne[2] << " (elementy wyzerowane)" << endl; 
cout << "zw[0]: " << zw[1] << " (jakies smieci)" << endl;
float tabliczka={0}; // mozna zerowac przy inicjalizacji

char literki[20];
memset(literki,'a',sizeof(literki));
cout << "Literki[17] = "<<literki[17]<<endl;

int tablica[2][4]={0};
tablicowa(tablica,2);
}
