#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void classic_selection_sort(int t[], int n)
{
    int i, j, min;
    int temp;
    for (i = 0; i < n-1; ++i) {
        min = i;
        for (j = i+1; j < n; ++j) {
            if (t[j] < t[min]) {
                min = j;
            }
        }
        if (min != i) {
            temp = t[i];
            t[i] = t[min];
            t[min] = temp;
        }
    }
}

void selection_sort_second(int* begin, int* end)
{
    int *i, *j, *min;
    int temp;
    for (i = begin; i != end; ++i) {
        min = i;
        for (j = i; j != end; ++j) {
            if (*j < *min) {
                min = j;
            }
        }
        if (*min != *i) {
            temp = *i;
            *i = *min;
            *min = temp;
        }
    }
}

template<typename Iterator> void selection_sort_with_iterators(Iterator begin, Iterator end)
{
    typedef typename iterator_traits<Iterator>::value_type value_type;
    value_type temp;
    for(; begin != end; begin++)
    {
        Iterator min = begin;
        for(Iterator j = (begin+1); j != end; j++)
        {
            if(*j < *min)
            {
                min = j;
            }
        }
        if(min != begin)
        {
            temp = *begin;
            *begin = *min;   
            *min = temp;
        }
    }
}

template <typename Iter>
void selection_sort(Iter begin, Iter end)
{
    for (; begin != end; ++begin)
    {
        iter_swap(begin, min_element(begin, end));
    }
}

int main()
{

    vector<int> vec;
    vec.push_back(5);
    vec.push_back(33);
    vec.push_back(9);
    vec.push_back(7);
    
    //selection_sort(vec.begin(), vec.end());
    //classic_selection_sort(&vec[0], vec.size());
    selection_sort_with_iterators(vec.begin(), vec.end());
    
    int tab[4] = {13,2,4141,222};
    selection_sort_second(tab, tab+4);

    for(int i=0;i<4;i++)
        cout << "  " << tab[i];
          
    
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << endl;
    }
    
    cout << endl;
    
    vector<double> dVec;
    dVec.push_back(5.12);
    dVec.push_back(5.001);
    dVec.push_back(1231.21);
    dVec.push_back(491.12);
    
    for(std::vector<double>::iterator it = dVec.begin(); it != dVec.end(); ++it)
    {
        cout << *it << endl;
    }    
    
    cout << "\n";
    
    selection_sort(dVec.begin(), dVec.end());

    for(std::vector<double>::iterator it = dVec.begin(); it != dVec.end(); ++it)
    {
        cout << *it << endl;
    }

}
