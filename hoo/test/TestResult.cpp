#include <hoo/test/TestResult.hh>

namespace hoo
{
    namespace test
    {
        TestResult::TestResult(const std::string &name, size_t assert_count, size_t failed_count)
            : _name(name),
              _assert_count(assert_count),
              _failed_count(failed_count)
        {
        }

        TestResult::TestResult(const TestResult &t)
            : _name(t._name),
              _assert_count(t._assert_count),
              _failed_count(t._failed_count)
        {
        }

        const std::string &TestResult::GetName() const
        {
            return this->_name;
        }

        const size_t TestResult::GetAssertCount() const
        {
            return this->_assert_count;
        }

        const size_t TestResult::GetFailedCount() const
        {
            return this->_failed_count;
        }

        const bool TestResult::IsSuccess() const
        {
            return (0 == this->_failed_count);
        }
    } // namespace test
} // namespace hoo