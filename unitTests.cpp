#include <cppunit/TestResult.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestAssert.h>
#include <cppunit/ui/text/TestRunner.h>
#include "ujList.h"

class ListTests : public CppUnit::TestCase
{
public:
    void runTest()
    {

    }
};


int main()
{
    ListTests* lTest = new ListTests();
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(lTest);

    runner.run();


}
