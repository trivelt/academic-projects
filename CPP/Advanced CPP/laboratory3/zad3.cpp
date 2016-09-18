#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
vector<int> numbers;
while(1)
{
	int number;
	cout << "Podaj liczbe: ";
	cin >> number;
	if(number == 0)
	{
		break;
	}
	numbers.push_back(number);
}

cout << "Min = " << *std::min_element(numbers.begin(), numbers.end()) << endl;
cout << "Max = " << *std::max_element(numbers.begin(), numbers.end()) << endl;

}
