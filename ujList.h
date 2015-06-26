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


    template<typename T> list<T>::element::element() : value(NULL), next(nullptr) {}
    template<typename T> list<T>::element::element(T val) : value(val), next(nullptr) {}


    template<typename T> list<T>::iterator::iterator()
    {
    }

    template<typename T> typename list<T>::iterator & list<T>::iterator::operator=(list<T>::element el)
    {
    }

    template<typename T> typename list<T>::iterator & list<T>::iterator::operator++()
    {
    }

    template<typename T> typename list<T>::iterator & list<T>::iterator::operator++(int)
    {
    }

    template<typename T> bool list<T>::iterator::operator==(list<T>::iterator other)
    {
    }

    template<typename T> bool list<T>::iterator::operator!=(list<T>::iterator other)
    {
    }

    template<typename T> T & list<T>::iterator::operator*()
    {
    }

    template<typename T> T * list<T>::iterator::operator->()
    {
    }


    template<typename T> list<T>::list() : head(nullptr) {}

    template<typename T> list<T>::list(const list & other)
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

        iterator insertedElement = this->begin();
        for(++it; it != other.end(); ++it)
        {
            insertedElement = this->insert(++insertedElement, *it);
        }
    }

    template<typename T> list<T>::~list()
    {
    }

    template<typename T> list<T> & list<T>::operator=(const list & other)
    {
    }

    template<typename T> bool list<T>::empty() const
    {
        return true;
    }

    template<typename T> size_t list<T>::size() const
    {
    }

    template<typename T> typename list<T>::iterator list<T>::begin()
    {
    }

    template<typename T> typename list<T>::iterator list<T>::end()
    {
    }

    template<typename T> void list<T>::clear()
    {
    }

    template<typename T> typename list<T>::iterator list<T>::insert(iterator pos, const T & value)
    {
        element* newElement = element(value);

        if(this->empty())
        {
            head = newElement;
            return iterator(newElement);
        }

        element* oldElement = *pos;
        newElement->next = oldElement;
        if(oldElement == head)
        {
            head = newElement;
        }
        else
        {
            element* previousElement = pos.previous;
            previousElement->next = newElement;
        }
        return iterator(newElement);
    }

    template<typename T> typename list<T>::iterator list<T>::erase(iterator pos)
    {
    }

}

#endif // UJLIST_H
