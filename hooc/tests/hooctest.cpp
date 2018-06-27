#include "ArithmeticStmtTest.hh"
#include "ModuleNameTest.hh"
#include "Logger.hh"

#include <iostream>
#include <cppunit/ui/text/TestRunner.h>

using namespace CppUnit;

int main(int argc, char** argv) {
    TextUi::TestRunner runner;
    runner.addTest(ArithmeticStmtTest::suite());
    runner.addTest(ModuleNameTest::suite());
    runner.run("", false, true, false);
}

