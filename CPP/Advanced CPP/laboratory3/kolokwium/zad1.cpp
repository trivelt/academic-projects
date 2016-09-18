#include "zad1.h"
#include <iostream>

int main()
{
    Stack<char> c;

    std::cout << c.size() << '\n';      // should print 0
    c.push('a');
    c.push('b');
    c.push('c');
    std::cout << c.size() << '\n';      // should print 3

    return 0;
}
