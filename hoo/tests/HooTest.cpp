#include "TypeTest.hh"
#include "ValueTest.hh"
#include "JITBasicTest.hh"
#include "MethodBasicTest.hh"

#include <cppunit/ui/text/TestRunner.h>


using namespace CppUnit;

int main() {
    TextUi::TestRunner runner;
    runner.addTest(TypeTest::suite());
    runner.addTest(ValueTest::suite());
    runner.addTest(JITBasicTest::suite());
    runner.addTest(MethodBasicTest::suite());
    runner.run("", false, true, false);
    return 0;
}

