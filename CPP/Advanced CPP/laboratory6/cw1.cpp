#include <iostream>
#include <typeinfo>
#include <boost/type_traits.hpp>
using namespace std;

template<class T> T myabs(T number)
{
    if(boost::is_signed<T>::value == false)
        {
            cout << "Unsigned type\n";
            return number;
        }
    if(number < 0)
        {
        if(boost::has_negate<T>::value)
            return -number;
        }
    else
        return number;
}

int main()
{
typedef int* a;
typedef char b;

cout << boost::is_pointer<a>::value << endl;
cout << boost::is_arithmetic<a>::value << endl;
cout << boost::is_const<char>::value << endl;
cout << boost::is_const<const char>::value << endl;

const char* napis = "abcd";
cout << typeid(napis).name() << endl;

unsigned int c = 5;
cout << myabs(c) << endl;
}
