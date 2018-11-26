#define BOOST_TEST_MODULE Module Name Test

#include "ParserDriver.hh"
#include <iostream>
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Test001_ModuleNameTest_TestValidName) {
    hooc::ParserDriver driver(std::cin, "Console.hoo");
    const std::string& moduleName = driver.GetModule().GetModuleName();
    const std::string& nameSpace = driver.GetModule().GetNameSpaace();
    BOOST_CHECK(0 == moduleName.compare("Console"));
    BOOST_CHECK(0 == nameSpace.compare(hooc::NAMESPACE_GLOBAL));
}

BOOST_AUTO_TEST_CASE(Test002_ModuleNameTest_ParitiallyValidName) {
    hooc::ParserDriver driver(std::cin, "0001Console001.hoo");
    const std::string& moduleName = driver.GetModule().GetModuleName();
    const std::string& nameSpace = driver.GetModule().GetNameSpaace();
    BOOST_CHECK(0 == moduleName.compare("Console001"));
    BOOST_CHECK(0 == nameSpace.compare(hooc::NAMESPACE_GLOBAL));
}

BOOST_AUTO_TEST_CASE(Test003_ModuleNameTest_InvalidName) {
    hooc::ParserDriver driver(std::cin, "0001.hoo");
    const std::string& moduleName = driver.GetModule().GetModuleName();
    const std::string& nameSpace = driver.GetModule().GetNameSpaace();
    BOOST_CHECK(true == moduleName.empty());
    BOOST_CHECK(0 == nameSpace.compare(hooc::NAMESPACE_GLOBAL));
}