#include <iostream>
#include "zad1.h"
#include "zad2.h"

int main()
{
	PositiveStackAdapter< int, Stack<int> > b;
    b.push(7);
    b.push(-13);
    b.push(2);
    while (! b.empty()) {
        std::cout << b.pop() << '\n';
    }        	  // should print 2 7

    return 0;
}
