#include "ArithmeticStmtTest.hh"
#include "ParserDriver.hh"

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <sstream>
using namespace CppUnit;
void ArithmeticStmtTest::SimpleTest() {
    std::stringstream stream("12 + 34 - 56;");
    hooc::ParserDriver driver(&stream, "test");
    CPPUNIT_ASSERT(0 == driver.Parse());
}

CppUnit::Test* ArithmeticStmtTest::suite() {
    TestSuite* arithmeticTestSuite = new TestSuite();
    arithmeticTestSuite->addTest(new TestCaller<ArithmeticStmtTest>("SimpleTest",
                                                                      &ArithmeticStmtTest::SimpleTest));
    return arithmeticTestSuite;
}
