#include <iostream>

template <typename T, int size = 16>
class Stack
{
protected:
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
        data[++top_index] = x;
    }

    T & top()
    {
        return data[top_index];
    }

    const T & top() const
    {
        return data[top_index];
    }

    void pop()
    {
        top_index--;
    }
};


template <typename T, int size = 16>
class DoublingStack : public Stack<T>
{

public:
	void push(const T & x)
		{
        Stack<T>::data[++Stack<T>::top_index] = x;		
        Stack<T>::data[++Stack<T>::top_index] = x;
		}

};


int main()
{
    Stack<int> a;

    a.push(1); a.push(2); a.push(3);
    while (! a.empty()) {
        std::cout << a.top() << '\n';
        a.pop();
    }                   // should print 3 2 1

    DoublingStack< int>  b;
   b.push(1); b.push(2); b.push(3);
         // should print 3 3 2 2 1 1
   while (! b.empty()) {
        std::cout << b.top() << '\n';
        b.pop();
    }            

    return 0;


}

