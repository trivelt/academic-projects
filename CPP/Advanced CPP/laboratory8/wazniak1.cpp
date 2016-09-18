#include <iostream>
using namespace std;

template<int N> struct Pow3
{
    enum{val = 3*Pow3<N-1>::val};
};

template<> struct Pow3<0>
{
    enum{val = 1 };
};

int main()
{
    cout <<  "Val = " << Pow3<3>::val << endl;
}