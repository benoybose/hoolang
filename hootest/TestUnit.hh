#include <string>
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <ostream>
#include <cstdint>

#include "TestResult.hh"

namespace hoo
{
    namespace test
    {
        // class TestUnit;
        // typedef void (*TestProc)(TestUnit*);

        /**
         * @brief A unit of test. It may contain multiple test cases
         */
        class TestUnit
        {
        protected:
            int _assert_count;
            int _failed_count;
            std::ostream &_out;
            std::map<std::string, std::function<void(void *)>> _procs;

        protected:
            TestUnit();

        protected:
            template <typename TImplementation>
            void RegisterTestCase(const std::string &name, void (TImplementation::*proc)())
            {
                std::function<void(void *)> test([proc](void *c) {
                    TImplementation *_this = (TImplementation *)c;
                    auto foo = std::bind(proc, _this);
                    foo();
                });
                _procs[name] = test;
            }

        public:
            /**
             * @brief Run test unit
             * 
             * @return std::list<TestResult> Result of the test running
             */
            std::list<TestResult> Run();

        private:
            std::ostream &Out() { return _out; }

        protected:
            void True(bool expr, const std::string &message);
            void False(bool expr, const std::string &message);
            void StringEqual(std::string s1, std::string s2, const std::string &message);

            template <typename T>
            void Equal(T v1, T v2, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if (v1 != v2)
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

            template <typename T>
            void NotEqual(T v1, T v2, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if (v1 == v2)
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

            template <typename T>
            void Null(T *v, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if (nullptr != v)
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

            template <typename T>
            void NotNull(T *v, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if (nullptr == v)
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

            template <typename T>
            void Throws(std::function<void()> code, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    try
                    {
                        code();
                        this->_failed_count += 1;
                        if (!message.empty())
                        {
                            Out() << message;
                        }
                    }
                    catch (T)
                    {
                        // todo: Do nothing
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                }
            }

            template <typename T>
            void DoesNotThrow(std::function<void()> code, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    try
                    {
                        code();
                    }
                    catch (T)
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
                    // todo: Do nothing
                }
            }

            void ThrowsAny(std::function<void()> code, const std::string &message);
            void DoesNotThrowAny(std::function<void()> code, const std::string &message);

            template <typename T>
            void Count(const std::vector<T> &items, size_t expected, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if (expected != items.size())
                    {
                        this->_failed_count += 1;
                        Out() << "Count test failed. Actual = \""
                              << std::to_string(items.size()) << "\". Expected = \""
                              << std::to_string(expected) << "\""
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message;
                            Out() << std::endl;
                        }
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                }
            }

            template <typename T>
            void Count(const std::list<T> &items, size_t expected, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if (expected != items.size())
                    {
                        this->_failed_count += 1;
                        Out() << "Count test failed. Actual = \""
                              << std::to_string(items.size()) << "\". Expected = \""
                              << std::to_string(expected) "\"";
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

            template <typename T>
            void At(const std::vector<T> &items, size_t index, T expected, const std::string &message)
            {
                try
                {
                    this->_assert_count += 1;
                    if ((0 > index) && (index >= items.size()))
                    {
                        this->_failed_count += 1;
                    }
                    else
                    {
                        auto original = items[index];
                        if (original != expected)
                        {
                            this->_failed_count += 1;
                        }
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                }
            }
        };
    } // namespace test
} // namespace hoo