#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

bool test(int a){return true;}

bool gt(int num)
    {
    std::greater<int> grt;
    return grt(num, 90);
    }

int main()
{
std::plus<int> pl;
std::cout << "2 + 3 = " << pl(2,3) << std::endl;

std::minus<double> sub;
std::cout << "14 - 2 = " << sub(14,2) << std::endl;

std::bit_and<bool> n;
std::cout << "True AND False = " << n(true, false) << std::endl;

std::equal_to<const char*> eq;
std::cout << "abc == abc? " << eq("abc","abc") << std::endl;

std::vector<int> vect;
vect.push_back(23);
vect.push_back(15);
vect.push_back(7);
vect.push_back(99);
vect.push_back(4014);
vect.push_back(81);
vect.push_back(2);

std::cout << "Vector: ";
for(std::vector<int>::iterator it = vect.begin(); 
    (it = find_if(it, vect.end(), gt)) != vect.end(); ++it )
    {
    std::cout << *it << " ";
    }
std::cout << "\n";

std::multiplies<int> mul;
int sum = std::accumulate(vect.begin(), vect.end()-4, 1, mul);
cout << "Mult = " << sum << endl;

sum = std::accumulate(vect.begin(), vect.end()-4, 0, sub);
cout << "Subst = " << sum << endl;
}
