#include <iostream>
#include <cmath>

/*
double integrate(double (*f)(double), double min, double max, double ds)
{
double integral = 0;
for(double x = min; x<max; x+=ds)
    {
    integral += f(x);
    }
return integral*ds;
}
*/


template<typename F> double integrate(F f, double min, double max, double ds)
{
double integral = 0;
for(double x = min; x<max; x+=ds)
    {
    integral += f(x);
    }   
return integral*ds;    
};

class Variable{
public:
    double operator()(double x){
        return x;
        }
};

class Constant{
    double _c;
public:
    Constant(double c) : _c(c){};
    double operator()(double x){return _c;}    
};

template<typename LHS, typename RHS > class AddExpr {
    LHS _lhs;
    RHS _rhs;
public:
    AddExpr(const LHS &l, const RHS &r) : _lhs(l), _rhs(r) {};
    double operator()(double x) {
        return _lhs(x) + _rhs(x);
    }
};

template<typename LHS,typename RHS > 
Add<LHS,RHS>  operator+(const LHS &l,
                        const RHS &r) {
  return Add<LHS,RHS>(l,r);
}; 

template<typename LHS > 
Add<LHS,Constant>  operator+(const LHS &l,
                        double r) {
  return Add<LHS,Constant>(l,Constant(r));
};
template<typename RHS > 
Add<Constant,RHS>  operator+(double l,
                        const RHS &r) {
 return Add<Constant,RHS>(Constant(l),r);
};   


int main()
{
//std::cout << integrate(sin, 0, 3.1415926, 0.01) << std::endl;
Variable x;
std::cout << integrate(Constant(1.0),0,1,0.001) << std::endl;
}
