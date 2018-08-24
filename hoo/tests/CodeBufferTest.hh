#ifndef CODEBUFFERTEST_HH
#define CODEBUFFERTEST_HH

#include "CodeBuffer.hh"

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cstddef>

using namespace hoo::jit;
using namespace CppUnit;


class CodeBufferTest: public TestFixture {
public:
    void Test001_CodeBufferTest();
    size_t GetPageSize();


public:
    static TestSuite* suite();
};


#endif //PROJECT_CODEBUFFERTEST_HH
