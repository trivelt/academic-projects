#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>
using namespace std;

int main()
{
vector<int> vect;
cout << "Int allocator type = " << 
        typeid(vector<int>::allocator_type).name() << endl;

typedef allocator<double> dAlloc;
dAlloc dA;
cout << "Double allocator type = " << 
        typeid(dA).name() << endl;

cout <<  "Allocator max value = " << 
        std::allocator_traits<dAlloc>::max_size << endl;
        
typedef dAlloc::pointer dAllocPointer;        
dAllocPointer pointer =  dA.allocate(4);
*pointer = 9.432215;

cout << "Value = " << *pointer << endl;
}

