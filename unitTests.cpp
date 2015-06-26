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

class ListBaseTest : public CppUnit::TestCase
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

        it = lista.begin();
        CPPUNIT_ASSERT_EQUAL(512, *it);
        CPPUNIT_ASSERT_EQUAL(512, it.previous->value);
        CPPUNIT_ASSERT_EQUAL(1024, it.previous->next->value);
        CPPUNIT_ASSERT_EQUAL(true, it.isHead);
        it++;
        CPPUNIT_ASSERT_EQUAL(512, it.previous->value);
        CPPUNIT_ASSERT_EQUAL(false, it.isHead);
        CPPUNIT_ASSERT_EQUAL(1024, *it);
        it++;
        CPPUNIT_ASSERT_EQUAL(true, lista.end() == it);
    }
};

class ListErasingTest : public CppUnit::TestCase
{
public:
    void runTest()
    {
        uj::list<int> lista;
        uj::list<int>::iterator it = lista.insert(lista.begin(), 256);
        it = lista.insert(it, 128);
        it = lista.insert(it, 64);
        it = lista.insert(it, 32);

        for(it=lista.begin(); it != lista.end(); it++)
        {
            std::cout << "Element = " << *it << "\n";
        }
        CPPUNIT_ASSERT_EQUAL(size_t(4), lista.size());
        lista.erase(lista.begin());
        CPPUNIT_ASSERT_EQUAL(size_t(3), lista.size());
        lista.erase(lista.begin());
        CPPUNIT_ASSERT_EQUAL(size_t(2), lista.size());
        lista.erase(lista.begin());
        CPPUNIT_ASSERT_EQUAL(size_t(1), lista.size());
        CPPUNIT_ASSERT_EQUAL(false, lista.empty());
        lista.erase(lista.begin());
        CPPUNIT_ASSERT_EQUAL(true, lista.empty());
        CPPUNIT_ASSERT_EQUAL(size_t(0), lista.size());

        std::cout << "\n\n";
        it=lista.begin();
        it = lista.insert(lista.begin(), 256);
        it = lista.insert(it, 128);
        it = lista.insert(it, 64);
        it = lista.insert(it, 32);

        it = lista.begin();
        it++;
        CPPUNIT_ASSERT_EQUAL(size_t(4), lista.size());
        lista.erase(it);
        CPPUNIT_ASSERT_EQUAL(size_t(3), lista.size());
        for(it=lista.begin(); it != lista.end(); it++)
        {
            std::cout << "Element = " << *it << "\n";
        }

    }
};


int main()
{
    ElementTest* elementTest = new ElementTest();
    IteratorTest* iteratorTest = new IteratorTest();
    ListBaseTest* listTest = new ListBaseTest();
    ListErasingTest* listErasingTest = new ListErasingTest();
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(elementTest);
    runner.addTest(iteratorTest);
    runner.addTest(listTest);
    runner.addTest(listErasingTest);

    runner.run();


}
