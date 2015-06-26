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

    /**
      * @brief Destruktor
      *
      * Destruktor listy. Usuwa z niej wszystkie elementy.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> list<T>::~list()
    {
        this->clear();
    }

    template<typename T> list<T> & list<T>::operator=(const list & other)
    {
    }

    /**
      * @brief Sprawdza czy lista jest pusta
      * @return true jesli lista jest pusta, w przeciwnym wypadku - false
      *
      * Funkcja sprawdzajaca czy lista zawiera niezerowa liczbe elementow.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> bool list<T>::empty() const
    {
        return (head == nullptr);
    }

    /**
      * @brief Rozmiar listy
      * @return Liczba elementow w liscie
      *
      * Funkcja obliczajaca i zwracajaca rozmiar listy.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> size_t list<T>::size() const
    {
        size_t counter = 0;
        for(iterator it=this->begin(); it != this->end(); ++it)
        {
            counter++;
        }
        return counter;
    }

    /**
      * @brief Zwraca iterator na poczatek listy
      * @return Iterator na pierwszy element listy
      *
      * Funkcja zwraca iterator wskazujacy na poczatek listy.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::begin()
    {
        return iterator(head);
    }

    /**
      * @brief Iterator poza lista
      * @return Iterator na miejsce za koncem listy
      *
      * Funkcja zwraca iterator wskazujacy na miejsce za koncem listy,
      * czyli wskaznik nullptr.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::end()
    {
        return iterator(nullptr);
    }

    /**
      * @brief Czyszczenie listy
      *
      * Funkcja usuwajaca z listy wszystkie elementy.
      *
      * Zlozonosc czasowa: O(n)
      */
    template<typename T> void list<T>::clear()
    {
        for(iterator it=this->begin(); it != this->end(); ++it)
        {
            this->erase(it);
        }
    }

    /**
      * @brief Dodawanie nowego elementu
      * @param Iterator wskazujacy na pozycje nowego elementu
      * @param Wartosc nowego elementu
      * @return Iterator na dodany element
      *
      * Funkcja wstawia nowy element bezposrednio przed elementem
      * wskazywanym przez podany iterator. Zwracanym obiektem jest
      * iterator na nowo utworzony element listy.
      *
      * Zlozonosc czasowa: O(1)
      */
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

    /**
      * @brief Usuwanie elementu z listy
      * @param Iterator wskazujacy na element do usuniecia
      * @return Iterator na element nastepny po usunietym
      *
      * Funkcja pobiera jako argument iterator do elementu listy
      * i usuwa go z niej. Zwracanym obiektem jest iterator do
      * elementu nastepnego po usunietym.
      *
      * Zlozonosc czasowa: O(1)
      */
    template<typename T> typename list<T>::iterator list<T>::erase(iterator pos)
    {
        element* elementToErase = *pos;
        if(elementToErase == head)
        {
            head = elementToErase->next;
        }
        else
        {
            element* previousElement = pos.previous;
            previousElement->next = elementToErase->next;
        }
        iterator nextElement(elementToErase->next);
        delete elementToErase;
        return nextElement;
    }

}

#endif // UJLIST_H
