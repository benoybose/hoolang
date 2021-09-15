/*
 * Copyright 2021 Benoy Bose
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

#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>
#include <hoo/emitter/UnitEmitter.hh>
#include <hoo/emitter/HooJIT.hh>
#include <llvm/Support/Errno.h>

#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace hoo::test;
using namespace hoo::parser;
using namespace hoo::emitter;

class AddMethodTest: public TestUnit
{
    public:
    AddMethodTest()
    {
        RegisterTestCase("TEST01",
        &AddMethodTest::TEST01);
        RegisterTestCase("TEST02",
        &AddMethodTest::TEST02);
        RegisterTestCase("TEST03",
        &AddMethodTest::TEST03);
        RegisterTestCase("TEST04",
        &AddMethodTest::TEST04);
        RegisterTestCase("TEST05",
        &AddMethodTest::TEST05);
    }

    void TEST01()
    {
        const std::string source = R"source(
        class Math {
            public add(a:int, b:int) : int {
                return a + b;
            }
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test01");
        auto result = jit->Execute<int64_t, int64_t, int64_t> ("Math$add", 321, 678);
        Equal<int64_t>(result, 999);

        for (auto index = -10000; index <= 10000; index++)
        {
            auto const offset = rand();
            auto sum = jit->Execute<int64_t, int64_t, int64_t> ("Math$add", index, offset);
            Equal<int64_t>(sum, index + offset);
        }        
    }

    void TEST02()
    {
        const std::string source = R"source(
        public add(a:int, b:int) : int {
            return a + b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test02");
        auto result = jit->Execute<int64_t, int64_t, int64_t> ("add", 321, 678);
        Equal<int64_t>(result, 999);

        for (auto index = -10000; index <= 10000; index++)
        {
            auto const offset = rand();
            auto sum = jit->Execute<int64_t, int64_t, int64_t> ("add", index, offset);
            Equal<int64_t>(sum, index + offset);
        }        
    }

    void TEST03()
    {
        const std::string source = R"source(
        public add(a:double, b:double) : double {
            return a + b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test03");
        auto result = jit->Execute<double, double, double> ("add", 1.314, 34.076);
        Equal<double>(result, 35.39);
    }

    void TEST04()
    {
        const std::string source = R"source(
        public add(a:int, b:double) : double {
            return a + b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test04");
        auto result = jit->Execute<double, int64_t, double> ("add", 1, 2.6);
        auto offset = fabs(3.6 - result);
        True(offset < 0.01);
    }

    void TEST05()
    {
        const std::string source = R"source(
        public add(a:double, b:int) : double {
            return a + b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test05");
        auto result = jit->Execute<double, double, int> ("add", 35.5, 2);
        auto offset = fabs(37.5 - result);
        True(offset < 0.01);
    }
};

HOO_TEST_CASE(AddMethodTest)
