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
#include <hoo/emitter/UnitEmitter.hh>
#include <hoo/emitter/HooJIT.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/parser/ParserDriver.hh>
#include <llvm/Support/Errno.h>

#include <string>

using namespace hoo::test;
using namespace hoo::parser;
using namespace hoo::emitter;

class SubMethodTest: public TestUnit
{
    public:
    SubMethodTest()
    {
        RegisterTestCase("TEST01",
        &SubMethodTest::TEST01);
        RegisterTestCase("TEST02",
        &SubMethodTest::TEST02);
        RegisterTestCase("TEST03",
        &SubMethodTest::TEST03);
        RegisterTestCase("TEST04",
        &SubMethodTest::TEST04);
        // RegisterTestCase("TEST05",
        // &SubMethodTest::TEST05);
        // RegisterTestCase("TEST06",
        // &SubMethodTest::TEST06);
        // RegisterTestCase("TEST07",
        // &SubMethodTest::TEST07);
        // RegisterTestCase("TEST08",
        // &SubMethodTest::TEST08);
        // RegisterTestCase("TEST09",
        // &SubMethodTest::TEST09);
        // RegisterTestCase("TEST10",
        // &SubMethodTest::TEST10);
        // RegisterTestCase("TEST11",
        // &SubMethodTest::TEST11);
        // RegisterTestCase("TEST12",
        // &SubMethodTest::TEST12);
        // RegisterTestCase("TEST13",
        // &SubMethodTest::TEST13);
        // RegisterTestCase("TEST14",
        // &SubMethodTest::TEST14);
    }

    void TEST01()
    {
        const std::string source = R"source(
        public sub(a:int, b:int) : int {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test01");
        auto result = jit->Execute<int64_t, int64_t, int64_t> ("sub", 321, 678);
        Equal<int64_t>(result, -357);
        result = jit->Execute<int64_t, int64_t, int64_t> ("sub", 678, 321);
        Equal<int64_t>(result, 357);
        auto const a = rand();
        auto const b = rand();
        result = jit->Execute<int64_t, int64_t, int64_t> ("sub", a, b);
        Equal<int64_t>(result, a - b);
    }

    void TEST02()
    {
        const std::string source = R"source(
        public sub(a:int, b:double) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test02");
        auto result = jit->Execute<double, int64_t, double> ("sub", 4, 1.6);
        DoubleEqual(result, 2.4);
        result = jit->Execute<double, int64_t, double> ("sub", 34, 3.4);
        DoubleEqual(result, 30.6);
        auto const a = rand();
        auto const b = rand() / 1.2;
        result = jit->Execute<double, int64_t, double> ("sub", a, b);
        DoubleEqual(result, a - b);
    }

    void TEST03()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:double) : int {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test03");
        });

        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 10);
    }

    void TEST04()
    {
        const std::string source = R"source(
        public sub(a:int, b:double) : int {
            return (int a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test04", true);
        auto result = jit->Execute<int64_t, int64_t, double>("sub", 10, 1.2);
        Equal<int64_t>(result, 8);
    }

    // void TEST03()
    // {
    //     auto ex = Throws<EmitterException>([] () {
    //         const std::string source = R"source(
    //         public sub(a:int, b:double) : int {
    //             return a - b;
    //         }
    //         )source";
    //         auto jit = std::move(* HooJIT::Create());
    //         jit->Evaluate(source, "test03");
    //     });
    //     auto error_code = ex.GetErrorNo();
    //     Equal<int>(error_code, 10);
    // }

    // void TEST04()
    // {
    //     const std::string source = R"source(
    //     public sub(a:int, b:double) : int {
    //         return (int a - b);
    //     }
    //     )source";
    //     auto jit = std::move(* HooJIT::Create());
    //     jit->Evaluate(source, "test04", true);
    //     auto result = jit->Execute<int64_t, int64_t, double>("sub", 4, 1.2);
    // }

    // void TEST02()
    // {
    //     const std::string source = R"source(
    //     public sub(a:int, b:int) : int {
    //         return a - b;
    //     }
    //     )source";
    //     auto jit = std::move(* HooJIT::Create());
    //     jit->Evaluate(source, "test02");
    //     auto result = jit->Execute<int64_t, int64_t, int64_t> ("sub", 321, 678);
    //     Equal<int64_t>(result, -357);

    //     for (auto index = -10000; index <= 10000; index++)
    //     {
    //         auto const offset = rand();
    //         auto sum = jit->Execute<int64_t, int64_t, int64_t> ("sub", index, offset);
    //         Equal<int64_t>(sum, index - offset);
    //     }
    // }

    // void TEST03()
    // {
    //     const std::string source = R"source(
    //     public sub(a:double, b:double) : double {
    //         return a - b;
    //     }
    //     )source";
    //     auto jit = std::move(* HooJIT::Create());
    //     jit->Evaluate(source, "test03");
    //     auto result = jit->Execute<double, double, double> ("sub", 1.314, 34.076);
    //     Equal<double>(result, -32.762);
    // }

    // void TEST04()
    // {
    //     const std::string source = R"source(
    //     public sub(a:int, b:double) : double {
    //         return a - b;
    //     }
    //     )source";
    //     auto jit = std::move(* HooJIT::Create());
    //     jit->Evaluate(source, "test04");
    //     auto result = jit->Execute<double, int64_t, double> ("sub", 35, 34.076);
    //     DoubleEqual(result, 0.924);
    // }

    void TEST05()
    {
        const std::string source = R"source(
        public sub(a:double, b:int) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test05");
        auto result = jit->Execute<double, double, int> ("sub", 35.5, 2);
        DoubleEqual(result, 33.5);
    }

    void TEST06()
    {
        const std::string source = R"source(
        public sub(a:byte, b:byte) : byte {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test06");
        auto result = jit->Execute<unsigned char, unsigned char, unsigned char> ("sub", 117, 56);
        Equal<unsigned char>(result, 61);
    }

    void TEST07()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
                public sub(a:byte, b:int) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test07", true);
        });
        auto const error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }

    void TEST08()
    {
        const std::string source = R"source(
            public sub(a:byte, b:int) : int {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test08");
        auto result = jit->Execute<long, unsigned char, long>("sub", 100, 300);
        Equal<long>(result, -200);
    }

    void TEST09()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:byte) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test09");
        });

        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 10);
    }

    void TEST10()
    {
        const std::string source = R"source(
        public sub(a:int, b:byte) : int {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test10");
        auto result = jit->Execute<long, long, unsigned char> ("sub", -200, 100);
        Equal<long>(result, -300);
    }

    void TEST11()
    {
        const std::string source = R"source(
        public sub(a:byte, b:double) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test11");
        auto result = jit->Execute<double, unsigned char, double> ("sub", 30, 31.1);
        DoubleEqual(result, -1.1);
    }

    void TEST12()
    {
        const std::string source = R"source(
        public sub(a:double, b:byte) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test12");
        auto result = jit->Execute<double, double, unsigned char> ("sub", 1245.5601, 221);
        DoubleEqual(result, 1024.5601);
    }

    void TEST13()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:byte) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test13", true);
        });
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }

    void TEST14()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:long, b:byte) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test14", true);
        });
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }
};

HOO_TEST_CASE(SubMethodTest)
