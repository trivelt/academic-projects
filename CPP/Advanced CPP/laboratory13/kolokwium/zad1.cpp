#include <algorithm>
#include <complex>
#include <iostream>

template <typename Iter>
void print_on_cout(Iter b, Iter e)
{
    if (b == e) {
        return;
    }
    while (true) {
        std::cout << *b;
        ++b;
        if (b == e) {
            break;
        }
        std::cout << ' ';
    }
    std::cout << '\n';
}

// Several simple functor classes with nested typedefs
// which specify types of arguments and results.

struct plus_two {
    typedef int argument_type;
    typedef int result_type;

    int operator()(int x) {
        return x + 2;
    }
};

struct square {
    typedef int argument_type;
    typedef int result_type;

    int operator()(int x) {
        return x * x;
    }
};

struct plus_three {
    typedef std::complex<double> argument_type;
    typedef std::complex<double> result_type;

    std::complex<double> operator()(std::complex<double> x) {
        return x + std::complex<double>(3.0, 0.0);
    }
};

struct minus_one_i {
    typedef std::complex<double> argument_type;
    typedef std::complex<double> result_type;

    std::complex<double> operator()(std::complex<double> x) {
        return x - std::complex<double>(0.0, 1.0);
    }
};

template <typename T, typename U> struct Functor
    {
    typedef typename U::argument_type argument_type;
    typedef typename T::result_type result_type;
    argument_type m_arg;
    
    Functor(argument_type arg)
        {
            m_arg = arg;
        }
    
    result_type operator()()
        {
        T t;
        U u;
        return t(u(arg));
        }
    };

template <typename T, typename U> typename T::result_type compose(T fun1, U fun2)
    {
    Functor<T,U> f;
    return &f();
    };
// An adapter class template and its auxiliary function template.



int main()
{
    int t[5] = { 7, 2, 6, 4, 5 };

    print_on_cout(t, t+5);      // should print 7 2 6 4 5

    std::transform(t, t+5, t, compose(plus_two(), square()));

    print_on_cout(t, t+5);      // should print 51 6 38 18 27

    std::complex<double> c[3] = { std::complex<double>(1.3, -5.4),
        std::complex<double>(0.0, 2.0), std::complex<double>(3.3, 1.5) };

    print_on_cout(c, c+3);      // should print (1.3,-5.4) (0,2) (3.3,1.5)

    std::transform(c, c+3, c, compose(plus_three(), minus_one_i()));

    print_on_cout(c, c+3);      // should print (4.3,-6.4) (3,1) (6.3,0.5)

    return 0;
}

