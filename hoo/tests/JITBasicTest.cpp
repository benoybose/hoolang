#define BOOST_TEST_MODULE JIT Basic Test

#include "JIT.hh"
#include "JITException.hh"

#include <boost/test/included/unit_test.hpp>

using namespace hoo;
using namespace hoo::jit;


BOOST_AUTO_TEST_CASE(Test001_CreateModule) {
    JIT jit;
    jit.CreateModule(MODULE_CLASS, "hoo");
    auto moduleNames = jit.GetModuleNames();
    BOOST_CHECK(1 == moduleNames.size());
    auto moduleName = *(moduleNames.begin());
    BOOST_CHECK(0 == moduleName.compare("hoo"));
    auto module = jit.GetModule(moduleName);
    auto moduleName2 = module.GetName();
    BOOST_CHECK(0 == moduleName2.compare(moduleName));
    BOOST_CHECK(MODULE_CLASS == module.GetModuleType());
}

BOOST_AUTO_TEST_CASE(Test002_CreateModule) {
    JIT jit;
    Module& module1 = jit.CreateModule(MODULE_CLASS, "class1");
    Module& module2 = jit.CreateModule(MODULE_CLASS, "class2");
    Module& module3 = jit.CreateModule(MODULE_INSTANCE, "instance1");

    auto moduleNames = jit.GetModuleNames();
    auto iterator = moduleNames.begin();
    BOOST_CHECK(iterator != moduleNames.end());

    auto moduleName = *(iterator);
    BOOST_CHECK(0 == moduleName.compare("class1"));
    BOOST_CHECK(0 == moduleName.compare(module1.GetName()));
    BOOST_CHECK(MODULE_CLASS == module1.GetModuleType());

    moduleName = *(++iterator);
    BOOST_CHECK(0 == moduleName.compare("class2"));
    BOOST_CHECK(0 == moduleName.compare(module2.GetName()));
    BOOST_CHECK(MODULE_CLASS == module2.GetModuleType());

    moduleName = *(++iterator);
    BOOST_CHECK(0 == moduleName.compare("instance1"));
    BOOST_CHECK(0 == moduleName.compare(module3.GetName()));
    BOOST_CHECK(MODULE_INSTANCE == module3.GetModuleType());

    BOOST_CHECK(++iterator == moduleNames.end());
}

BOOST_AUTO_TEST_CASE(Test003_CreateModule) {
    JIT jit;
    jit.CreateModule(MODULE_CLASS, "class");
    BOOST_CHECK_THROW(jit.CreateModule(MODULE_CLASS, "class"), hoo::jit::JITException);
}
