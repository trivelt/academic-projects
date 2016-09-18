/* Literaly, przyrostki etc. */
#include <iostream>
using std::cout;
using std::endl;

int main()
{
int liczba = 010;
cout << "Liczba to "<< liczba << endl;
liczba = 0x010;
cout << "Liczba to "<< liczba << endl;
liczba = 10lu; // unsigned long
cout << "Liczba to "<< liczba << endl;

cout << "Liczba 19.25425 jako float: "<<19.25425f<<endl;
cout << "Ta sama liczba jako long double: "<<19.25425l<<endl;

cout << u8"Jakis znak specjalny: \u2620" <<endl; // UTF-16
cout << "Klucz wiolinowy \U0001D11E" << endl; // UTF-32

std::string napis(R"(Surowy literal napisowy \n\n)");
std::string as = R"(ls /home/docs | grep ".pdf")";
cout << napis <<endl << as << endl;;
}
