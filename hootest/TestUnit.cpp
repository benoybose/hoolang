#include <string>
#include <iostream>
#include <list>
#include <exception>

#include "TestResult.hh"
#include "TestUnit.hh"

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
                    TestResult result(name, this->_assert_count - asserted_count,
                                      this->_failed_count - failed_count);
                    results.push_back(result);
                }
                catch (...)
                {
                    Out() << "failed test case: \"" << name << "\"" << std::endl;
                }
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
            }
        }

        void TestUnit::StringEqual(std::string s1, std::string s2, const std::string &message)
        {
            try
            {
                this->_assert_count += 1;
                if (0 != s1.compare(s2))
                {
                    this->_failed_count += 1;
                    if (!message.empty())
                    {
                        Out() << message;
                    }
                }
            }
            catch (...)
            {
                this->_failed_count += 1;
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
            }
        }
    } // namespace test
} // namespace hoo