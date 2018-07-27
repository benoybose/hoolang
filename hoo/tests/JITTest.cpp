#include <cppunit/TestAssert.h>
#include "JIT.hh"
#include "JITTest.hh"

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

using namespace hoo;
using namespace hoo::jit;
using namespace CppUnit;

void JITBasicTest::Test001_TestAddModule() {
    JIT jit;
    jit.CreateModule(MODULE_CLASS, "hoo");
    auto moduleNames = jit.GetModuleNames();
    CPPUNIT_ASSERT(1 == moduleNames.size());
    auto moduleName = *(moduleNames.begin());
    CPPUNIT_ASSERT(0 == moduleName.compare("hoo"));
    auto module = jit.GetModule(moduleName);
    auto moduleName2 = module.GetName();
    CPPUNIT_ASSERT(0 == moduleName2.compare(moduleName));
    CPPUNIT_ASSERT(MODULE_CLASS == module.GetModuleType());
}

TestSuite *JITBasicTest::suite() {
    TestSuite *testSuite = new TestSuite();
    testSuite->addTest(new TestCaller<JITBasicTest>(std::string("Test001_TestAddModule"),
                                                    &JITBasicTest::Test001_TestAddModule));
    return testSuite;
}
