#include <iostream>

template<class T, class U> void print_on_cout_if(T begin, T end, U f)
{
	while(begin != end)
	{
		if(f(*begin) == true)
			{
			std::cout << *begin << " ";
			}
	begin++;
	}
}

#include <vector>

class LessThanFive
{
public:
    bool operator()(int x) {
        return x < 5;
    }
};

int main()
{
    LessThanFive f;

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(3);

    print_on_cout_if(vec.begin(), vec.end(), f);    // should print 1 4 3

    int arr[5] = { 7, 2, 9, 64, 1 };

    print_on_cout_if(arr, arr + 5, f);      // should print 2 1

    return 0;
}
