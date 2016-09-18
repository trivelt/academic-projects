#include <iostream>

//*******************************************
template<bool flag, typename T1, typename T2> struct If_then_else {
typedef T1 Result;
};

template <typename T1, typename T2>
struct If_then_else<false, T1, T2> {
typedef T2 Result;
};

template<typename T1, typename T2> struct Greater_then {
typedef typename If_then_else<sizeof(T1)<sizeof(T2), T1, T2>::result result;
};
//************************************************/


//*
template<typename T> class Is_class {
    typedef char one;
    typedef struct{char c[2];} two;

    template<typename U> static one test(int U::*);
    template<typename U> static two test(...);
    
    public:
    enum{ yes = (sizeof(test<T>(0))==sizeof(one))};

};

class A{};

//**/

template<typename T1,typename T2> struct Promote {
typedef typename 
        If_then_else<(sizeof(T1) > sizeof(T2)),
                     T1,
                     typename If_then_else< (sizeof(T1)< sizeof(T2)),
                                           T2,
                                           void>::Result >::Result Result;
};


int main()
{

std::cout << Is_class<A>::yes << std::endl;
}
