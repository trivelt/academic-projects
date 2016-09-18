#include <iostream>
using namespace std;

template <typename T, int N = 16>
class Stack
{
private:
    T _rep[N];
    int _top;

public:
    Stack() : _top(0){}

    void push(T x)
	{
        _rep[_top++] = x;
    }

    T pop()
	{
        return _rep[--_top];
    }

    bool empty()
	{
        return _top == 0;
    }

	int size()
	{
		return _top;
	}
};

template<int N> class Stack<char, N>
{
private:
	char _rep[N];
	int _top;
public:
    Stack() : _top(0){}

    void push(char x)
	{
        _rep[_top++] = x;
    }

	void push(const char* s)
	{
	const char* p = s;
	while(*p != '\0')
		{
		push(*p);
		p++;
		}
	}

    char pop()
	{
        return _rep[--_top];
    }

    bool empty()
	{
        return _top == 0;
    }

	int size()
	{
		return _top;
	}
};


int main()
{

Stack<char> stos;
stos.push("abcd");
cout << stos.pop() << endl;
cout << stos.pop() << endl;
cout << stos.pop() << endl;
cout << stos.pop() << endl;
stos.push('u');
cout << stos.pop() << endl;
stos.push("xy");
cout << stos.pop() << endl;
cout << stos.pop() << endl;

}
