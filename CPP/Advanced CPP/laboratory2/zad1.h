#include <iostream>
using namespace std;

template <typename T>
T sum_of_array_elements(T * begin, T * end)
{
	T sum = (T)0;
		while(begin < end)
		{
		sum = sum + *begin;
		begin++;
		}
	return sum;
}
