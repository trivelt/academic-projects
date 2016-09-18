#include <iostream>

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


template <typename T, typename U >
class DoublingStack
{
	U stack;
public:
	void pop()
	{
	return stack.pop();
	}

	bool empty()
	{
		return stack.empty();
	}
	
	T& top()
	{
	return stack.top();
	}

	void push(const T& x)
	{
		stack.push(x);
		stack.push(x);
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

    DoublingStack< int, Stack<int> > b;
    b.push(1); b.push(2); b.push(3);
         // should print 3 3 2 2 1 1
   while (! b.empty()) {
        std::cout << b.top() << '\n';
        b.pop();
    }           

    return 0;


}

