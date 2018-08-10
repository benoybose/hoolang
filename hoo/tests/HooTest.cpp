#include "TypeTest.hh"
#include "ValueTest.hh"

#include <cppunit/ui/text/TestRunner.h>
#include "JITBasicTest.hh"

using namespace CppUnit;

int main() {
    TextUi::TestRunner runner;
    runner.addTest(TypeTest::suite());
    runner.addTest(ValueTest::suite());
    runner.addTest(JITBasicTest::suite());
    runner.run("", false, true, false);
    return 0;
}

