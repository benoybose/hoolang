//
// Created by COMP on 23-06-2018.
//

#ifndef HOOC_MODULENAMETEST_HH
#define HOOC_MODULENAMETEST_HH

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>

class ModuleNameTest: public CppUnit::TestFixture {
public:
    void TestValidName();
    void TestPartiallyValidName();
    void TestInvalidName();

public:
    static CppUnit::Test* suite();
};


#endif //HOOC_MODULENAMETEST_HH
