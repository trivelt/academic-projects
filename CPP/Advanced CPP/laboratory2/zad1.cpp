#include <iostream>
#include "zad1.h"
using namespace std;

int main()
{
int tab[4] = {1,3,5,2};
int sum = sum_of_array_elements<int>(tab, tab+4);
cout << "Sum=" << sum << endl;;
}
