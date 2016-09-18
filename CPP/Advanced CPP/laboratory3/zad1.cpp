#include <iostream>
#include <vector>
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

int min, max;
vector<int>::iterator it=numbers.begin();
min = max = *it;
it++;

for(; it != numbers.end(); it++)
{

	if(*it < min)
		min = *it;
	if(*it > max)
		max = *it;
}

cout << "Min = " << min << endl;
cout << "Max = " << max << endl;

}
