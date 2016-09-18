#include <iostream>
#include <vector>
#include <limits>
#include <iterator>
using namespace std;

template<class Iter> typename iterator_traits<Iter>::value_type min_from_sequence(Iter begin, Iter end)
{
	typedef typename iterator_traits<Iter>::value_type value_type;
	if(begin == end)
		{
		value_type min_value = numeric_limits<value_type>::min();
		return min_value;
		}

	value_type min = *begin;
	begin++;
	while(begin != end)
		{
		if(*begin < min)
			min = *begin;
		begin++;
		}
	return min;
}

int main()
{

vector<int> v;
v.push_back(23);
v.push_back(15);
v.push_back(3);
cout << "Minimum = " << min_from_sequence(v.begin(), v.end()) << endl;

v.clear();
cout << "Minimum = " << min_from_sequence(v.begin(), v.end()) << endl;
}
