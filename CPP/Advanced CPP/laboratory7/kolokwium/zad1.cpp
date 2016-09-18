#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <typeinfo>
using namespace std;

template<typename Iter, typename T>
bool binary_search(Iter b, Iter e, T x)
{
    Iter i = lower_bound(b, e, x);
    if (i != e && !(x < *i))
        return true;
    else
        return false; 
}

template<typename Iter, typename T>
bool linear_search(Iter b, Iter e, T x)
{
    while(b != e)
    {
        if(*b == x)
            return true;
        b++;
    }
    return false;
}



template <typename Iter, typename T>
bool search_in_sorted_sequence(Iter b, Iter e, T x)
{
    typedef typename iterator_traits<Iter>::iterator_category category;
    if(typeid(category) == typeid(std::random_access_iterator_tag))
        binary_search(b, e, x);
    else
        linear_search(b, e, x);       
}
int main()
{
    int arr[5] = { 1, 2, 3, 4, 5 };

    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(9);

    std::list<int> lst;
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(6);
    lst.push_back(7);

    std::cout << std::boolalpha;    // print booleans as "true"/"false"

    std::cout << search_in_sorted_sequence(arr, arr + 5, 1)
                    << '\n';    // should print "true"

    std::cout << search_in_sorted_sequence(vec.begin(), vec.end(), 5)
                    << '\n';    // should print "false"

    std::cout << search_in_sorted_sequence(lst.begin(), lst.end(), 7)
                    << '\n';    // should print "true"

    return 0;
}

