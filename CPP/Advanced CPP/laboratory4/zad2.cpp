#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;


class isEven {
	public:
	bool operator()(int n)
	{
		return (n%2 == 0);
	}
};


int main()
{
srand(time(0));
vector<int> randTab;
for(int i=0;i<20;i++)
	{
	randTab.push_back(rand());
	cout << "random number = " << randTab[i] << endl;
	}

isEven iE;
int sum = count_if(randTab.begin(), randTab.end(), iE);
cout << "Sum = " << sum << endl;

}
