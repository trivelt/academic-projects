#include <iostream>
using std::cout; 
using std::endl;

int a = 5; // zmienna globalna
namespace JakasPrzestrzen
	{
	int a = 10;
	int b = 3;
	}

namespace	// nienazwana przestrzen 
	{
	int c = 4;
	// int a = 0; NIE MOZNA, konflikt z globalną
	}

int main()
{
int a = 15;
int c = 40;
cout << "a lokalne: "<<a<<endl<<"a globalne: "<<::a<<endl;
using namespace JakasPrzestrzen;
cout << "a nadal lokalne: "<<a<<endl;
cout << "a z JakiejsPrzestrzenii: "<<JakasPrzestrzen::a<<endl;
cout << "b z JakiejsPrzestrzenii: "<<b<<endl;
int b=6;
cout << "teraz b: "<<b<<endl;
cout << "c z nienazwanej przestrzenii: "<<::c<<endl;
cout << "c lokalne: "<<c<<endl;
}
