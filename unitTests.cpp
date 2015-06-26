#include <cppunit/TestResult.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>
#include <cppunit/ui/text/TestRunner.h>
#include "ujList.h"
#include <iostream>

uj::list<int>::element* nulptr = nullptr;

class ElementTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        uj::list<int>::element firstElement(29);
        CPPUNIT_ASSERT_EQUAL(29, firstElement.value);
        CPPUNIT_ASSERT_EQUAL(nulptr, firstElement.next);

        firstElement.value = 30;
        firstElement.next = &firstElement;
        uj::list<int>::element secondElement(firstElement);
        CPPUNIT_ASSERT_EQUAL(30, secondElement.value);
        CPPUNIT_ASSERT_EQUAL(&firstElement, secondElement.next);
    }
};

class IteratorTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        uj::list<int>::element firstElement(100);
        uj::list<int>::element secondElement(200);
        uj::list<int>::element thirdElement(300);
        firstElement.next = &secondElement;
        secondElement.next = &thirdElement;
        uj::list<int>::iterator it;
        CPPUNIT_ASSERT_EQUAL(nulptr, it.previous);
        CPPUNIT_ASSERT_EQUAL(false, it.isHead);

        uj::list<int>::iterator it2(&firstElement, true);
        CPPUNIT_ASSERT_EQUAL(&firstElement, it2.previous);
        CPPUNIT_ASSERT_EQUAL(200, it2.previous->next->value);
        CPPUNIT_ASSERT_EQUAL(true, it2.isHead);
        CPPUNIT_ASSERT_EQUAL(false, it == it2);
        CPPUNIT_ASSERT_EQUAL(true, it != it2);

        uj::list<int>::iterator it3(it2);
        CPPUNIT_ASSERT_EQUAL(true, it2 == it3);
        CPPUNIT_ASSERT_EQUAL(false, it2 != it3);

        it3.isHead = false;
        CPPUNIT_ASSERT_EQUAL(false, it2 == it3);
        CPPUNIT_ASSERT_EQUAL(true, it2 != it3);
        it3.isHead = true;


        CPPUNIT_ASSERT_EQUAL(100, *it2);
        ++it2;
        CPPUNIT_ASSERT_EQUAL(200, *it2);
        ++it2;
        CPPUNIT_ASSERT_EQUAL(300, *it2);

        CPPUNIT_ASSERT_EQUAL(100, *it3);
        it3++;
        CPPUNIT_ASSERT_EQUAL(200, *it3);
        it3++;
        CPPUNIT_ASSERT_EQUAL(300, *it3);
    }
};

class ListTests : public CppUnit::TestCase
{
public:
    void runTest()
    {
        uj::list<int> lista;
        CPPUNIT_ASSERT_EQUAL(true, lista.empty());
        CPPUNIT_ASSERT_EQUAL(size_t(0), lista.size());

        uj::list<int>::iterator it = lista.begin();
        CPPUNIT_ASSERT_EQUAL(lista.head, it.previous);
        CPPUNIT_ASSERT_EQUAL(nulptr, it.previous);
        CPPUNIT_ASSERT_EQUAL(false, it.isHead);

        uj::list<int>::iterator itEnd = lista.end();
        CPPUNIT_ASSERT_EQUAL(lista.tail, itEnd.previous);
        CPPUNIT_ASSERT_EQUAL(nulptr, itEnd.previous);

        uj::list<int>::iterator newEl = lista.insert(it, 512);
        CPPUNIT_ASSERT_EQUAL(true, newEl.isHead);
        CPPUNIT_ASSERT_EQUAL(512, *newEl);
        CPPUNIT_ASSERT_EQUAL(nulptr, newEl.previous->next);
        CPPUNIT_ASSERT_EQUAL(false, lista.empty());
        CPPUNIT_ASSERT_EQUAL(lista.tail, newEl.previous);

        newEl++;
        CPPUNIT_ASSERT_EQUAL(false, newEl.isHead);
        CPPUNIT_ASSERT_EQUAL(lista.tail, newEl.previous);
        CPPUNIT_ASSERT_EQUAL(size_t(1), lista.size());

        uj::list<int>::iterator secondEl = lista.insert(newEl, 1024);
        CPPUNIT_ASSERT_EQUAL(false, secondEl.isHead);
        CPPUNIT_ASSERT_EQUAL(size_t(2), lista.size());
        CPPUNIT_ASSERT_EQUAL(false, (lista.tail == newEl.previous));
        CPPUNIT_ASSERT_EQUAL(lista.tail, newEl.previous->next);


//        element* head;

//        list(); // O(1)
//        list(const list & other); // O(n)
//        ~list(); // O(n)

//        list & operator=(const list & other); // O(n)
//        bool empty() const; // O(1)
//        size_t size() const; // O(n)

//        iterator begin() const; // O(1)
//        iterator end() const; // O(1)

//        void clear(); // O(n)
//        iterator insert(iterator pos, const T & value); // O(1)
//        iterator erase(iterator pos); // O(1)

    }
};


int main()
{
    ElementTest* elementTest = new ElementTest();
    IteratorTest* iteratorTest = new IteratorTest();
    ListTests* listTest = new ListTests();
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(elementTest);
    runner.addTest(iteratorTest);
    runner.addTest(listTest);

    runner.run();


}
