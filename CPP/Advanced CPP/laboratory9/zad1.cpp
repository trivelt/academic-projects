#include <iostream>

template<typename T> class StackIterator;

template <typename T, int N = 100>
class Stack
{
private:
    T _rep[N];
    int _top;
    friend class StackIterator<T>;

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
	

    StackIterator<T> begin()
    {
        return StackIterator<T>(_rep, _top);
    }
    
    StackIterator<T> end()
    {
        return StackIterator<T>(_rep, -1);
    }
};


template<typename T> class StackIterator
{
private:
    int stackIteratorIndex;
    T* _stackTab;
    friend class Stack<T>;

public:
    StackIterator(T* stackTab, int top) : _stackTab(stackTab), stackIteratorIndex(top-1)
    {
    }

    T operator*()
    {
        return _stackTab[stackIteratorIndex];    
    }
    
    StackIterator& operator++()
    {
        stackIteratorIndex--;
        return *this;
    }
    
    StackIterator& operator++(T)
    {
        stackIteratorIndex--;
        return *this;    
    }
        
    bool operator==(StackIterator other)        
    {
        return (this->stackIteratorIndex == other.stackIteratorIndex);
    }
       
    bool operator!=(StackIterator other)
    {
        return !(*this == other);
    }       
    
};

int main()
{
Stack<int> st;
st.push(5);
st.push(9);
st.push(21);
st.push(424);

StackIterator<int> it = st.begin();
std::cout << "Value = " << *it << std::endl;
std::cout << "Value = " << *(it++) << std::endl;
std::cout << "Value = " << *(++it) << std::endl;

for(StackIterator<int> it = st.begin(); it != st.end(); it++)
    {
    std::cout << "Loop iterator, value = " << *it << std::endl;
    }

}
