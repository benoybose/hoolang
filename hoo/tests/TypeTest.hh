//
// Created by COMP on 27-06-2018.
//

#ifndef PROJECT_TYPETEST_HH
#define PROJECT_TYPETEST_HH

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>

using namespace CppUnit;

class TypeTest: public TestFixture {
public:
    void Test001_BasicTypes();

public:
    static Test* suite();
};


#endif //PROJECT_TYPETEST_HH
