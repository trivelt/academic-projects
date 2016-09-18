#include <iostream>
using namespace std;

class myFunctor {
	public:
	bool operator()(int n)
	{
		return (n%2 == 0);
	}
};



int main()
{

	myFunctor f1;
	cout << "F1: " << f1(4) << endl;
	cout << "F2: " << f1(3) << endl;
}
