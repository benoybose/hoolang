/*
 * Copyright 2020 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

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
                    if (failed_count == this->_failed_count) {
                        this->_failed_count += 1;
                    }
                    Out() << "failed test case: \"" << name << "\"" << std::endl;
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

        void TestUnit::StringEqual(std::string orignal, std::string expected, const std::string &message)
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