//
// Created by COMP on 21-06-2018.
//

#ifndef HOOC_PARSERARITHMETICTEST_HH
#define HOOC_PARSERARITHMETICTEST_HH

#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>


class ArithmeticStmtTest: public CppUnit::TestFixture {
public:
    void Test001_12plus34();
    static CppUnit::Test* suite();
};


#endif //HOOC_PARSERARITHMETICTEST_HH
