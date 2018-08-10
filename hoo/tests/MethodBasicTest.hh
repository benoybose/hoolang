//
// Created by COMP on 10-08-2018.
//

#ifndef PROJECT_METHODBASICTEST_HH
#define PROJECT_METHODBASICTEST_HH

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>

using namespace CppUnit;

class MethodBasicTest: public TestFixture {

public:
    static TestSuite* suite();

public:
    void Test001_CreateMethod();
    void Test002_CreateMethod();
};


#endif //PROJECT_METHODBASICTEST_HH
