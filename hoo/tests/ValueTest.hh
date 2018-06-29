//
// Created by COMP on 27-06-2018.
//

#ifndef PROJECT_VALUETEST_HH
#define PROJECT_VALUETEST_HH

#include "Value.hh"

#include <cppunit/TestFixture.h>
#include <cppunit/Test.h>

using namespace CppUnit;

class ValueTest: public TestFixture {
public:
    void Test001_IntegerValue();
    void Test002_BooleanValue();
    void Test003_DoubleValue();
    void Test004_ObjectValue();
    void Test005_StringValue();
    void Test006_ByteValue();
    void Test007_CharacterValue();

public:
    static Test* suite();
};


#endif //PROJECT_VALUETEST_HH
