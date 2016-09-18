#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T, int size = 16>
class Stack
{
    T data[size];
    int top_index;

public:
    Stack() : top_index(-1)
    { }

    bool empty() const
    {
        return top_index == -1;
    }

    void push(const T & x)
    {
        if(top_index+1 == size)
        {
            throw out_of_range("Cannot push into full stack");
        }
        data[++top_index] = x;
    }

   T pop()
	{
	    if(empty())
	    {
	        throw out_of_range("Cannot pop from empty stack");
	    }
        return data[--top_index];
    }
};

int main()
{
    Stack<int,2> a;
    
    try {
    a.push(1);
    a.push(2);
    a.push(3);
    }
    catch(exception &e)
        {
            cout << "Exception: " << e.what() << endl;
        }    
    
    try {
    cout << a.pop() << endl;
    cout << a.pop() << endl;
    cout << a.pop() << endl;
    cout << a.pop() << endl;
    }
    catch(exception &e)
        {
            cout << "Exception: " << e.what() << endl;
        }
    
    return 0;
}
