#define BOOST_TEST_MODULE Method Basic Test

#include "JIT.hh"
#include "Module.hh"
#include "Method.hh"
#include "Value.hh"

#include <boost/test/included/unit_test.hpp>
#include <vector>

using namespace hoo;
using namespace hoo::jit;

BOOST_AUTO_TEST_CASE(Test001_CreateMethod) {
    JIT jit;
    Module module = jit.CreateModule(MODULE_INSTANCE, "default");
    Method method = module.CreateMethod("main");
    BOOST_CHECK(0 == TYPENAME_VOID.compare(method.GetReturnType()));
    BOOST_CHECK(0 == method.GetName().compare("main"));
    BOOST_CHECK(method.GetModule() == &module);
    auto params = method.GetParameters();
    BOOST_CHECK(params.begin() == params.end());
}

BOOST_AUTO_TEST_CASE(Test002_CreateMethod) {
    JIT jit;
    Module module = jit.CreateModule(MODULE_INSTANCE, "default");
    Method method = module.CreateMethod("add");
    MethodParam x = method.AddParameter(TYPENAME_INTEGER, "x");
    MethodParam y = method.AddParameter(TYPENAME_INTEGER, "y");
    method.SetReturnType(TYPENAME_INTEGER);

    BOOST_CHECK(0 == x.GetName().compare("x"));
    BOOST_CHECK(0 == x.GetType().compare(TYPENAME_INTEGER));
    BOOST_CHECK(0 == x.GetOrdinal());

    BOOST_CHECK(0 == y.GetName().compare("y"));
    BOOST_CHECK(0 == y.GetType().compare(TYPENAME_INTEGER));
    BOOST_CHECK(1 == y.GetOrdinal());

    auto params = method.GetParameters();
    BOOST_CHECK(2 == params.size());

    auto iterator = params.begin();
    BOOST_CHECK(iterator != params.end());

    auto paramx = *(iterator);
    BOOST_CHECK(nullptr != paramx);
    auto paramy = *(++iterator);
    BOOST_CHECK(nullptr != paramy);

    BOOST_CHECK(0 == paramx->GetName().compare(x.GetName()));
    BOOST_CHECK(0 == paramx->GetType().compare(x.GetType()));
    BOOST_CHECK(paramx->GetOrdinal() == x.GetOrdinal());

    BOOST_CHECK(0 == paramy->GetName().compare(y.GetName()));
    BOOST_CHECK(0 == paramy->GetType().compare(y.GetType()));
    BOOST_CHECK(paramy->GetOrdinal() == y.GetOrdinal());
}

BOOST_AUTO_TEST_CASE(Test003_CreateMethod) {
    JIT jit;
    Module module = jit.CreateModule(MODULE_INSTANCE, "Default");
    Method &testMethod = module.CreateMethod("test");
    auto code = testMethod.Generate();
    auto code_expected = std::vector<uint8_t> { 0x55, 0x48, 0x89, 0xe5, 0x5d, 0xc3 };
    BOOST_CHECK(code.size() == code_expected.size());
    for(size_t index = 0; index < code.size(); index++) {
        BOOST_CHECK(code[index] == code_expected[index]);
    }
}

