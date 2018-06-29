//
// Created by COMP on 27-06-2018.
//

#include "TypeTest.hh"
#include "HooTypes.hh"

#include <cstdio>

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

using namespace CppUnit;

void TypeTest::Test001_BasicTypes() {
    CPPUNIT_ASSERT((sizeof(void*) == 8));
    CPPUNIT_ASSERT((sizeof(hoo::Integer) == 8));
    CPPUNIT_ASSERT((sizeof(hoo::Character) == sizeof(void*)));
    CPPUNIT_ASSERT((sizeof(hoo::String) == sizeof(void*)));
    CPPUNIT_ASSERT((sizeof(hoo::Boolean) == 1));
    CPPUNIT_ASSERT((sizeof(hoo::Double) == 16));
}

Test* TypeTest::suite() {
    TestSuite* type_test_suite = new TestSuite();
    type_test_suite->addTest(new TestCaller<TypeTest>("Test001_BasicTypes",
                             &TypeTest::Test001_BasicTypes));
    return type_test_suite;
}