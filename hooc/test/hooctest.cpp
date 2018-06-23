#include "ArithmeticStmtTest.hh"
#include "Logger.hh"

#include <iostream>
#include <cppunit/ui/text/TestRunner.h>

using namespace CppUnit;

int main(int argc, char** argv) {
    hooc::Logger::Info("Testing");
    TextUi::TestRunner runner;
    runner.addTest(ArithmeticStmtTest::suite());
    runner.run("", false, true, false);
}

