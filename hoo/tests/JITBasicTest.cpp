#include <cppunit/TestAssert.h>
#include "JIT.hh"
#include "JITBasicTest.hh"
#include "JITException.hh"

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

using namespace hoo;
using namespace hoo::jit;
using namespace CppUnit;

void JITBasicTest::Test001_CreateModule() {
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

void JITBasicTest::Test002_CreateModule() {
    JIT jit;
    Module& module1 = jit.CreateModule(MODULE_CLASS, "class1");
    Module& module2 = jit.CreateModule(MODULE_CLASS, "class2");
    Module& module3 = jit.CreateModule(MODULE_INSTANCE, "instance1");

    auto moduleNames = jit.GetModuleNames();
    auto iterator = moduleNames.begin();
    CPPUNIT_ASSERT(iterator != moduleNames.end());

    auto moduleName = *(iterator);
    CPPUNIT_ASSERT(0 == moduleName.compare("class1"));
    CPPUNIT_ASSERT(0 == moduleName.compare(module1.GetName()));
    CPPUNIT_ASSERT(MODULE_CLASS == module1.GetModuleType());

    moduleName = *(++iterator);
    CPPUNIT_ASSERT(0 == moduleName.compare("class2"));
    CPPUNIT_ASSERT(0 == moduleName.compare(module2.GetName()));
    CPPUNIT_ASSERT(MODULE_CLASS == module2.GetModuleType());

    moduleName = *(++iterator);
    CPPUNIT_ASSERT(0 == moduleName.compare("instance1"));
    CPPUNIT_ASSERT(0 == moduleName.compare(module3.GetName()));
    CPPUNIT_ASSERT(MODULE_INSTANCE == module3.GetModuleType());

    CPPUNIT_ASSERT(++iterator == moduleNames.end());
}

void JITBasicTest::Test003_CreateModule() {
    JIT jit;
    jit.CreateModule(MODULE_CLASS, "class");
    CPPUNIT_ASSERT_THROW(jit.CreateModule(MODULE_CLASS, "class"), hoo::jit::JITException);
}

TestSuite *JITBasicTest::suite() {
    TestSuite *testSuite = new TestSuite(); 
    testSuite->addTest(new TestCaller<JITBasicTest>(std::string("Test001_CreateModule"),
                                                    &JITBasicTest::Test001_CreateModule));
    testSuite->addTest(new TestCaller<JITBasicTest>(std::string("Test002_CreateModule"),
                                                    &JITBasicTest::Test002_CreateModule));
    testSuite->addTest(new TestCaller<JITBasicTest>(std::string("Test003_CreateModule"),
                                                    &JITBasicTest::Test003_CreateModule));
    return testSuite;
}


