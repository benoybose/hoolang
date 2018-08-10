//
// Created by COMP on 27-07-2018.
//

#ifndef PROJECT_JITTEST_HH
#define PROJECT_JITTEST_HH

#include "JIT.hh"

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>

using namespace hoo::jit;
using namespace CppUnit;

class JITBasicTest: public TestFixture {
public:
    void Test001_CreateModule();
    void Test002_CreateModule();
    void Test003_CreateModule();

public:
    static TestSuite* suite();
};

#endif //PROJECT_JITTEST_HH
