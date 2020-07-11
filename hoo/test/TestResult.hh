#include <string>
#include <cstdint>

#ifndef _HOO_TEST_TESTRESULT_
#define _HOO_TEST_TESTRESULT_

namespace hoo
{
    namespace test
    {
        class TestResult
        {
        private:
            std::string _name;
            size_t _assert_count;
            size_t _failed_count;

        public:
            TestResult(const std::string &name, size_t assert_count, size_t failed_count);
            TestResult(const TestResult &test_result);

        public:
            const std::string &GetName() const;
            const size_t GetAssertCount() const;
            const size_t GetFailedCount() const;
            const bool IsSuccess() const;
        };
    } // namespace test
} // namespace hoo

#endif // _HOO_TEST_TESTRESULT_