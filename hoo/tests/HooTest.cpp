#include "TypeTest.hh"
#include "ValueTest.hh"

#include <cppunit/ui/text/TestRunner.h>

using namespace CppUnit;

int main() {
    TextUi::TestRunner runner;
    runner.addTest(TypeTest::suite());
    runner.addTest(ValueTest::suite());
    runner.run("", false, true, false);
    return 0;
}

