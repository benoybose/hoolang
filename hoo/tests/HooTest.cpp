#include "TypeTest.hh"
#include "JITBasicTest.hh"
#include "MethodBasicTest.hh"
#include "CodeBufferTest.hh"

#include <cppunit/ui/text/TestRunner.h>


using namespace CppUnit;

int main() {
    TextUi::TestRunner runner;
    runner.addTest(TypeTest::suite());
    runner.addTest(JITBasicTest::suite());
    runner.addTest(MethodBasicTest::suite());
    runner.addTest(CodeBufferTest::suite());
    runner.run("", false, true, false);
    return 0;
}

