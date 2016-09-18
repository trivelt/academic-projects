#include <iostream>
#include "zad2.h"

int main()
{
    Register<double> k;

    k.put(2.00);
    k.put(3.95);
    k.put(1.50);
    std::cout << k.get() << '\n';   // should print 7.45

    k.put(2.00);
    std::cout << k.get() << '\n';   // should print 9.45

    k.reset();
    std::cout << k.get() << '\n';   // should print 0.0

    return 0;
}

