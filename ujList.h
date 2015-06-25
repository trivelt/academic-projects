#ifndef UJLIST_H
#define UJLIST_H
#include <iostream>
#include <iterator>

namespace uj {

    template<typename T> class list
    {
    public:
        typedef T value_type;
        typedef value_type& reference;
        typedef const reference const_reference;

        struct element
        {
            T value;
            element* next;

            element();
            element(T val);
        };

        struct iterator : std::iterator<std::random_access_iterator_tag, T*>
        {
            element* previous;

            iterator();
            iterator(element* ptr);
            iterator & operator=(element el);
            iterator & operator++();
            iterator & operator++(int);
            bool operator==(iterator other);
            bool operator!=(iterator other);
            T & operator*();
            T * operator->();
        };

        element* head;

        list(); // O(1)
        list(const list & other); // O(n)
        ~list(); // O(n)

        list & operator=(const list & other); // O(n)
        bool empty() const; // O(1)
        size_t size() const; // O(n)

        iterator begin(); // O(1)
        iterator end(); // O(1)

        void clear(); // O(n)
        iterator insert(iterator pos, const T & value); // O(1)
        iterator erase(iterator pos); // O(1)
    };
}

template<typename T> uj::list<T>::element::element() : value(NULL), next(nullptr) {}
template<typename T> uj::list<T>::element::element(T val) : value(val), next(nullptr) {}


template<typename T> uj::list<T>::iterator::iterator()
{
}

template<typename T> typename uj::list<T>::iterator & uj::list<T>::iterator::operator=(uj::list<T>::element el)
{
}

template<typename T> typename uj::list<T>::iterator & uj::list<T>::iterator::operator++()
{
}

template<typename T> typename uj::list<T>::iterator & uj::list<T>::iterator::operator++(int)
{
}

template<typename T> bool uj::list<T>::iterator::operator==(uj::list<T>::iterator other)
{
}

template<typename T> bool uj::list<T>::iterator::operator!=(uj::list<T>::iterator other)
{
}

template<typename T> T & uj::list<T>::iterator::operator*()
{
}

template<typename T> T * uj::list<T>::iterator::operator->()
{
}


template<typename T> uj::list<T>::list() : head(nullptr) {}

template<typename T> uj::list<T>::list(const list & other)
{
    iterator it = other.begin();
    if(other.empty())
    {
        head = nullptr;
    }
    else
    {
        element headElement(*it);
        head = &headElement;
    }

    int pos = 1;
    for(++it; it != other.end(); ++it)
    {
        this->insert(pos, *it);
    }
}

template<typename T> uj::list<T>::~list()
{
    ;
}

template<typename T> bool uj::list<T>::empty() const
{
    return true;
}


#endif // UJLIST_H
