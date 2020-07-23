#include <string>
#include <functional>
#include <map>
#include <vector>
#include <list>
#include <ostream>
#include <cstdint>
#include <typeinfo>
#include <memory>

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

        public:
            void True(bool expr, const std::string &message = "");
            void False(bool expr, const std::string &message = "");
            void StringEqual(std::string orignal, std::string expected,
                             const std::string &message = "");

            template <typename T>
            void Equal(T original, T expected, const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (original != expected)
                    {
                        this->_failed_count += 1;
                        Out() << "Equal test failed. "
                              << "Original = \"" << original << "\". "
                              << "Expected = \"" << expected << "\"."
                              << std::endl;

                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"Equal\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Equal\" failed.");
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
                        throw std::runtime_error("test \"NotEqual\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"NotEqual\" failed.");
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
                        throw std::runtime_error("test \"Null\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Null\" failed.");
                }
            }

            template <typename T>
            void NotNull(T *v, const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (nullptr == v)
                    {
                        this->_failed_count += 1;
                        Out() << "NotNull test failed." << std::endl;
                        if (!message.empty())
                        {
                            Out() << message;
                        }
                        throw std::runtime_error("test \"NotNull\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"NotNull\" failed.");
                }
            }

            template <typename T>
            void Null(std::shared_ptr<T> v, const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (v)
                    {
                        this->_failed_count += 1;
                        Out() << "Null test failed." << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"Null\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Null\" failed.");
                }
            }

            template <typename T>
            void NotNull(std::shared_ptr<T> v, const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (!v)
                    {
                        this->_failed_count += 1;
                        Out() << "NotNull test failed." << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"NotNull\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"NotNull\" failed.");
                }
            }

            template <typename TExceptionType>
            void Throws(std::function<void()> code, const std::string &message = "")
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
                        throw std::runtime_error("test \"Throws\" failed.");
                    }
                    catch (TExceptionType)
                    {
                        // do nothing
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Throws\" failed.");
                }
            }

            template <typename T>
            void DoesNotThrow(std::function<void()> code, const std::string &message = "")
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
                        Out() << "DoesNotThrow test failed. The given code has thrown '"
                              << typeid(T).name()
                              << "'" << std::endl;
                        if (!message.empty())
                        {
                            Out() << message;
                        }
                        throw std::runtime_error("test \"DoesNotThrow\" failed.");
                    }
                }
                catch (...)
                {
                    // todo: Do nothing
                }
            }

            template <typename T, typename TReturn>
            TReturn DoesNotThrowAndReturn(std::function<TReturn()> code,
                                          const std::string &message = "")
            {
                TReturn *defaultValue = nullptr;
                try
                {
                    this->_assert_count += 1;
                    try
                    {
                        TReturn value = code();
                        return value;
                    }
                    catch (T)
                    {
                        this->_failed_count += 1;
                        Out() << "DoesNotThrowAndReturn test failed. The given code has thrown '"
                              << typeid(T).name()
                              << "'" << std::endl;
                        if (!message.empty())
                        {
                            Out() << message;
                        }
                        return *(defaultValue);
                    }
                }
                catch (...)
                {
                    return *(defaultValue);
                }
            }

            void ThrowsAny(std::function<void()> code, const std::string &message);
            void DoesNotThrowAny(std::function<void()> code, const std::string &message);

            template <typename T>
            void NotEmpty(const std::list<T> &items, const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (0 == items.size())
                    {
                        this->_failed_count += 1;
                        Out() << "NotEmpty test failed. "
                              << "The provided list is empty."
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"NotEmpty\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"NotEmpty\" failed.");
                }
            }

            template <typename T>
            void Empty(const std::list<T> &items, const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (0 < items.size())
                    {
                        this->_failed_count += 1;
                        Out() << "Empty test failed. "
                              << "The provided list contains " << items.size() << " items."
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"Empty\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Empty\" failed.");
                }
            }

            template <typename T>
            void Count(const std::vector<T> &items, size_t expected,
                       const std::string &message = "")
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
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"Count\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Count\" failed.");
                }
            }

            template <typename T>
            void Count(const std::list<T> &items, size_t expected,
                       const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (expected != items.size())
                    {
                        this->_failed_count += 1;
                        Out() << "Count test failed. Actual = \""
                              << std::to_string(items.size())
                              << "\". Expected = \""
                              << std::to_string(expected)
                              << "\"."
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"Count\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Count\" failed.");
                }
            }

            template <typename T>
            void At(const std::vector<T> &items, size_t index, T expected,
                    const std::string &message = "")
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
                            Out() << "Value at index " << index << " failed. "
                                  << ". Actual = \"" << std::to_string(original) << "\""
                                  << ". Expected = \"" << std::to_string(expected) << "\"."
                                  << std::endl;
                            if (!message.empty())
                            {
                                Out() << message << std::endl;
                            }
                            throw std::runtime_error("test \"At\" failed.");
                        }
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"At\" failed.");
                }
            }

            template <typename TExpected, typename TOriginal>
            void IsA(TOriginal value, const std::string &message = "")
            {
                try
                {
                    auto casted = dynamic_cast<TExpected *>(value);
                    if (casted == nullptr)
                    {
                        this->_failed_count++;
                        Out() << "IsA test failed. "
                              << ". Actual = \"" << typeid(TOriginal).name() << "\""
                              << ". Expected = \"" << typeid(TExpected).name() << "\""
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"IsA\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"IsA\" failed.");
                }
            }

            template <typename TExpected, typename TOriginal>
            std::shared_ptr<TExpected> IsA(std::shared_ptr<TOriginal> value, const std::string &message = "")
            {
                std::shared_ptr<TExpected> casted;
                try
                {
                    casted = std::dynamic_pointer_cast<TExpected>(value);
                    if (!casted)
                    {
                        this->_failed_count++;
                        Out() << "IsA test failed. "
                              << ". Actual = \"" << typeid(TOriginal).name() << "\""
                              << ". Expected = \"" << typeid(TExpected).name() << "\""
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"IsA\" failed.");
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"IsA\" failed.");
                }
                return casted;
            }

            template <typename TType>
            void Equal(std::list<TType> &original,
                       const std::list<TType> &expected,
                       const std::string &message = "")
            {
                try
                {
                    this->_assert_count += 1;
                    if (original.size() != expected.size())
                    {
                        this->_failed_count += 1;
                        Out() << "List equal test failed. Both list has different size." << std::endl
                              << "Size of original list is " << original.size() << ", while "
                              << "size of expected list is " << expected.size() << "."
                              << std::endl;
                        if (!message.empty())
                        {
                            Out() << message << std::endl;
                        }
                        throw std::runtime_error("test \"Equal\" failed.");
                    }

                    auto original_itr = original.begin();
                    auto expected_itr = expected.begin();
                    auto index = 0;

                    while ((original_itr != original.end()) &&
                           (expected_itr != expected.end()))
                    {
                        auto original_value = *(original_itr);
                        auto expected_value = *(expected_itr);
                        if (original_value != expected_value)
                        {
                            this->_failed_count++;
                            Out() << "Value at [" << index << "] is not matching. "
                                  << "Original [" << index << "] = " << original_value << ". "
                                  << "Expected [" << index << "] = " << expected_value << ". "
                                  << std::endl;

                            if (!message.empty())
                            {
                                Out() << message << std::endl;
                            }

                            throw std::runtime_error("test \"Equal\" failed.");
                        }
                        original_itr++;
                        expected_itr++;
                        index++;
                    }
                }
                catch (...)
                {
                    this->_failed_count += 1;
                    throw std::runtime_error("test \"Equal\" failed.");
                }
            }
        };
    } // namespace test
} // namespace hoo