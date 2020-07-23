#include <string>
#include <iostream>
#include <list>
#include <exception>

#include <hoo/test/TestResult.hh>
#include <hoo/test/TestUnit.hh>

namespace hoo
{
    namespace test
    {
        TestUnit::TestUnit() : _assert_count(0), _failed_count(0), _out(std::cerr) {}

        std::list<TestResult> TestUnit::Run()
        {
            std::list<TestResult> results;
            this->_assert_count = 0;
            this->_failed_count = 0;

            for (auto &proc : this->_procs)
            {
                const auto name = proc.first;
                const auto asserted_count = this->_assert_count;
                const auto failed_count = this->_failed_count;

                auto test = proc.second;
                try
                {
                    test(this);
                }
                catch (...)
                {
                    if (failed_count == this->_failed_count)
                    {
                        this->_failed_count += 1;
                    }
                    Out() << "failed test procedure: \"" << name << "\"" << std::endl;
                }

                TestResult result(name, this->_assert_count - asserted_count,
                                  this->_failed_count - failed_count);
                results.push_back(result);
            }
            return results;
        }

        void TestUnit::True(bool expr, const std::string &message)
        {
            this->_assert_count++;
            if (!expr)
            {
                this->_failed_count++;
                if (!message.empty())
                {
                    Out() << message;
                }
                throw std::runtime_error("test \"True\" failed.");
            }
        }

        void TestUnit::False(bool expr, const std::string &message)
        {
            this->_assert_count++;
            if (expr)
            {
                this->_failed_count++;
                if (!message.empty())
                {
                    Out() << message;
                }
                throw std::runtime_error("test \"False\" failed.");
            }
        }

        void TestUnit::StringEqual(std::string orignal,
                                   std::string expected, const std::string &message)
        {
            try
            {
                this->_assert_count += 1;
                if (0 != orignal.compare(expected))
                {
                    this->_failed_count += 1;
                    Out() << "String equality failed. Actual = \""
                          << orignal << "\". "
                          << "Expected = \""
                          << expected << "\"."
                          << std::endl;
                    if (!message.empty())
                    {
                        Out() << message << std::endl;
                    }
                    throw std::runtime_error("test \"StringEqual\" failed.");
                }
            }
            catch (...)
            {
                this->_failed_count += 1;
                throw std::runtime_error("test \"StringEqual\" failed.");
            }
        }

        void TestUnit::ThrowsAny(std::function<void()> code, const std::string &message)
        {
            try
            {
                this->_assert_count += 1;
                code();
                this->_failed_count += 1;
                if (!message.empty())
                {
                    Out() << message;
                }
                throw std::runtime_error("test \"ThrowsAny\" failed.");
            }
            catch (...)
            {
            }
        }

        void TestUnit::DoesNotThrowAny(std::function<void()> code, const std::string &message)
        {
            try
            {
                this->_assert_count += 1;
            }
            catch (...)
            {
                this->_failed_count += 1;
                if (!message.empty())
                {
                    Out() << message;
                }
                throw std::runtime_error("test \"DoesNotThrowAny\" failed.");
            }
        }
    } // namespace test
} // namespace hoo