#include <iostream>
#include <memory>
using namespace std;

class A
{
public:
~A(){cout << "DESTRUCTOR" << endl;}

};

template<typename T> void val(T p) {
};

template<typename T> void ref_1(T& p) {
};

template<typename T> void ref_2(T& p) {

};

int main()
{
auto_ptr<int> pi(new int(343));
cout << *pi << endl;

auto_ptr<int> pi2(new int);
pi2 = pi;

//cout << *pi << endl;
cout << *pi2 << endl;

val(pi2);
bool nl = (&pi2 != NULL);
cout << *pi2 << endl;
cout << nl << endl;

auto_ptr<A> pa(new A());
A* wsk = new A();

return 0;
}
