#ifndef _HOO_TEST_H
#define _HOO_TEST_H
#include <hoo/test/TestResult.hh>
#include <hoo/test/TestUnit.hh>

#define HOO_TEST_CASE(TESTCLASSNAME) \
int main() \
{ \
    TESTCLASSNAME test;\
    auto results = test.Run();\
    for (auto result : results)\
    {\
        if (!result.IsSuccess())\
        {\
            return -1;\
        }\
    }\
    return 0;\
}\

#endif // _HOO_TEST_H