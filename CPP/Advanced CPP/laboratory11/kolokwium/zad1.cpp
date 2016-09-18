#include <iostream>
#include <list>
#include <vector>
#include <type_traits>

// KOMPILOWAC Z --std=c++11

template<typename T>struct is_floating_point : std::integral_constant<
                               bool,
                               std::is_same<float, typename std::remove_cv<T>::type>::value  ||
                               std::is_same<double, typename std::remove_cv<T>::type>::value  ||
                               std::is_same<long double, typename std::remove_cv<T>::type>::value
                           > {};
                           

int main()
{
    // print booleans as "true"/"false"
    std::cout << std::boolalpha;

    // should print "true"
    std::cout << is_floating_point<float>::value << '\n';
    std::cout << is_floating_point<double>::value << '\n';

    // should print "false"
    std::cout << is_floating_point<int>::value << '\n';
    std::cout << is_floating_point<char>::value << '\n';
    std::cout << is_floating_point< std::list<float> >::value << '\n';
    std::cout << is_floating_point< std::vector<long> >::value << '\n';

    return 0;
}
