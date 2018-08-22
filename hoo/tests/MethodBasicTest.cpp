#include "MethodBasicTest.hh"
#include "JIT.hh"
#include "Module.hh"
#include "Method.hh"
#include "Value.hh"

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <vector>

using namespace hoo;
using namespace hoo::jit;

TestSuite *MethodBasicTest::suite() {
    TestSuite *testSuite = new TestSuite();
    testSuite->addTest(new TestCaller<MethodBasicTest>("Test001_CreateMethod",
                                                       &MethodBasicTest::Test001_CreateMethod));
    testSuite->addTest(new TestCaller<MethodBasicTest>("Test002_CreateMethod",
                                                       &MethodBasicTest::Test002_CreateMethod));
    testSuite->addTest(new TestCaller<MethodBasicTest>("Test003_CreateMethod",
                                                       &MethodBasicTest::Test003_CreateMethod));
    return testSuite;
}

void MethodBasicTest::Test001_CreateMethod() {
    JIT jit;
    Module module = jit.CreateModule(MODULE_INSTANCE, "default");
    Method method = module.CreateMethod("main");
    CPPUNIT_ASSERT(0 == TYPENAME_VOID.compare(method.GetReturnType()));
    CPPUNIT_ASSERT(0 == method.GetName().compare("main"));
    CPPUNIT_ASSERT(method.GetModule() == &module);
    auto params = method.GetParameters();
    CPPUNIT_ASSERT(params.begin() == params.end());
}

void MethodBasicTest::Test002_CreateMethod() {
    JIT jit;
    Module module = jit.CreateModule(MODULE_INSTANCE, "default");
    Method method = module.CreateMethod("add");
    MethodParam x = method.AddParameter(TYPENAME_INTEGER, "x");
    MethodParam y = method.AddParameter(TYPENAME_INTEGER, "y");
    method.SetReturnType(TYPENAME_INTEGER);

    CPPUNIT_ASSERT(0 == x.GetName().compare("x"));
    CPPUNIT_ASSERT(0 == x.GetType().compare(TYPENAME_INTEGER));
    CPPUNIT_ASSERT(0 == x.GetOrdinal());

    CPPUNIT_ASSERT(0 == y.GetName().compare("y"));
    CPPUNIT_ASSERT(0 == y.GetType().compare(TYPENAME_INTEGER));
    CPPUNIT_ASSERT(1 == y.GetOrdinal());

    auto params = method.GetParameters();
    CPPUNIT_ASSERT(2 == params.size());

    auto iterator = params.begin();
    CPPUNIT_ASSERT(iterator != params.end());

    auto paramx = *(iterator);
    CPPUNIT_ASSERT(nullptr != paramx);
    auto paramy = *(++iterator);
    CPPUNIT_ASSERT(nullptr != paramy);

    CPPUNIT_ASSERT(0 == paramx->GetName().compare(x.GetName()));
    CPPUNIT_ASSERT(0 == paramx->GetType().compare(x.GetType()));
    CPPUNIT_ASSERT(paramx->GetOrdinal() == x.GetOrdinal());

    CPPUNIT_ASSERT(0 == paramy->GetName().compare(y.GetName()));
    CPPUNIT_ASSERT(0 == paramy->GetType().compare(y.GetType()));
    CPPUNIT_ASSERT(paramy->GetOrdinal() == y.GetOrdinal());
}

void MethodBasicTest::Test003_CreateMethod() {
    JIT jit;
    Module module = jit.CreateModule(MODULE_INSTANCE, "Default");
    Method &testMethod = module.CreateMethod("test");
    auto code = testMethod.Generate();
    auto code_expected = std::vector<uint8_t> { 0x55, 0x48, 0x89, 0xe5, 0x5d, 0xc3 };
    CPPUNIT_ASSERT(code.size() == code_expected.size());
    for(size_t index = 0; index < code.size(); index++) {
        CPPUNIT_ASSERT(code[index] == code_expected[index]);
    }
}

