//
// Created by COMP on 23-06-2018.
//

#include "ModuleNameTest.hh"
#include "ParserDriver.hh"

#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>


using namespace CppUnit;

void ModuleNameTest::TestValidName() {
    hooc::ParserDriver driver(std::cin, "Console.hoo");
    const std::string& moduleName = driver.GetModule().GetModuleName();
    const std::string& nameSpace = driver.GetModule().GetNameSpaace();
    CPPUNIT_ASSERT(0 == moduleName.compare("Console"));
    CPPUNIT_ASSERT(0 == nameSpace.compare(hooc::NAMESPACE_GLOBAL));
}

void ModuleNameTest::TestPartiallyValidName() {
    hooc::ParserDriver driver(std::cin, "0001Console001.hoo");
    const std::string& moduleName = driver.GetModule().GetModuleName();
    const std::string& nameSpace = driver.GetModule().GetNameSpaace();
    CPPUNIT_ASSERT(0 == moduleName.compare("Console001"));
    CPPUNIT_ASSERT(0 == nameSpace.compare(hooc::NAMESPACE_GLOBAL));
}

void ModuleNameTest::TestInvalidName() {
    hooc::ParserDriver driver(std::cin, "0001.hoo");
    const std::string& moduleName = driver.GetModule().GetModuleName();
    const std::string& nameSpace = driver.GetModule().GetNameSpaace();
    CPPUNIT_ASSERT(true == moduleName.empty());
    CPPUNIT_ASSERT(0 == nameSpace.compare(hooc::NAMESPACE_GLOBAL));
}

CppUnit::Test* ModuleNameTest::suite() {
    TestSuite* theSuite = new TestSuite();
    theSuite->addTest(new TestCaller<ModuleNameTest>("Valid module name",
                                                     &ModuleNameTest::TestValidName));
    theSuite->addTest(new TestCaller<ModuleNameTest>("Partially valid module name",
                                                     &ModuleNameTest::TestPartiallyValidName));
    theSuite->addTest(new TestCaller<ModuleNameTest>("Invalid module name",
                                                     &ModuleNameTest::TestInvalidName));
    return theSuite;
}