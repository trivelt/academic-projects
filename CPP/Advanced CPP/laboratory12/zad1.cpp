#include <iostream>
#include <functional>

// dane jest double f(double, double)
// opakuj adapter, ktory jako pierwszy argument bedzie podawal 4.5
// binder1st<typ_funktora> (f, 4.5);
// bind1st(f, 4.5);

double f(double a, double b)
{return a+b;}

class F {
public:
double operator()(double a, double b)
{return a+b;}
};

int main()
{
F f1;
//std::binder1st<F> g(f1, 4.5);

//auto p1 = std::bind1st(f<double>(, 4.5);

}

