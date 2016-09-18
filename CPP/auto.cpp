/* Dedukcja typu - auto 
Kompilowac z flaga 
-std=c++0x
*/
#include <iostream>
using namespace std;

int main()
{
auto x = 4.5; // float 
cout << x << " rozmiar to "<<sizeof(x)<<endl;
auto y=5; // int 
cout << y << " rozmiar to "<<sizeof(y)<<endl;

auto z = new auto("test");
cout << *z << endl;
}
