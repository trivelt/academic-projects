#include <iostream>
#include <cstdlib> // dla atoi()
#include <sstream> // dla istringstream
using namespace std;

int main(int argc, char* argv[])
{
cout << "==== PROGRAM "<<argv[0]<<" ===="<<endl;
if(argc<3)
	{
	cout << "Musisz podac 2 argumenty!"<<endl;
	return 1;
	}
int arg1 = atoi(argv[1]);
int arg2 = atoi(argv[2]);
cout << "Suma podanych liczb wynosi " << (arg1+arg2) <<endl;

/**************************************
ALTERNATYWNA WERSJA ODCZYTU ARGUMENTOW
**************************************/

istringstream ss(argv[1]);
string slowo;
ss>>slowo;
if (ss.eof())
	{ // przywracamy czytanie strumienia do poczatku 
	ss.clear( ss.rdstate() & ~ios::eofbit );
	}
ss.str(argv[2]);
double liczba1;
ss >> liczba1;
cout << "Slowo "<<slowo<<" i liczba "<<liczba1/2<<endl;
}
