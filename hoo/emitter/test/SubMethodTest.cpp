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
        RegisterTestCase("TEST05",
        &SubMethodTest::TEST05);
        RegisterTestCase("TEST06",
        &SubMethodTest::TEST06);
        RegisterTestCase("TEST07",
        &SubMethodTest::TEST07);
        RegisterTestCase("TEST08",
        &SubMethodTest::TEST08);
        RegisterTestCase("TEST09",
        &SubMethodTest::TEST09);
        RegisterTestCase("TEST10",
        &SubMethodTest::TEST10);
        RegisterTestCase("TEST11",
        &SubMethodTest::TEST11);
        RegisterTestCase("TEST12",
        &SubMethodTest::TEST12);
        RegisterTestCase("TEST13",
        &SubMethodTest::TEST13);
        RegisterTestCase("TEST14",
        &SubMethodTest::TEST14);
        RegisterTestCase("TEST15",
        &SubMethodTest::TEST15);
        RegisterTestCase("TEST16",
        &SubMethodTest::TEST16);
        RegisterTestCase("TEST17",
        &SubMethodTest::TEST17);
        RegisterTestCase("TEST18",
        &SubMethodTest::TEST18);
        RegisterTestCase("TEST19",
        &SubMethodTest::TEST19);
        RegisterTestCase("TEST20",
        &SubMethodTest::TEST20);
        RegisterTestCase("TEST21",
        &SubMethodTest::TEST21);
        RegisterTestCase("TEST22",
        &SubMethodTest::TEST22);
        RegisterTestCase("TEST23",
        &SubMethodTest::TEST23);
        RegisterTestCase("TEST24",
        &SubMethodTest::TEST24);
        RegisterTestCase("TEST25",
        &SubMethodTest::TEST25);
        RegisterTestCase("TEST26",
        &SubMethodTest::TEST26);
        RegisterTestCase("TEST27",
        &SubMethodTest::TEST27);
        RegisterTestCase("TEST28",
        &SubMethodTest::TEST28);
        RegisterTestCase("TEST29",
        &SubMethodTest::TEST29);
        RegisterTestCase("TEST30",
        &SubMethodTest::TEST30);
        RegisterTestCase("TEST31",
        &SubMethodTest::TEST31);
        RegisterTestCase("TEST32",
        &SubMethodTest::TEST32);
    }

    /**
     * Test subtract an integer from another integer and returns integer
     **/
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

    /**
     * Test subtract an integer from another integer and try to return byte
     **/
    void TEST02()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:int) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test02");
        });

        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 10);
    }

    /**
     * Test subtract an integer from another integer and returns a byte through casting
     **/
    void TEST03()
    {
        const std::string source = R"source(
        public sub(a:int, b:int) : byte {
            return (byte a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test03");
        auto result = jit->Execute<uint8_t, int64_t, int64_t>("sub", 300, 141);
        Equal<uint8_t>(result, 159);
    }

    /**
     * Test subtract from an integer from another integer and returns a double
     **/
    void TEST04()
    {
        const std::string source = R"source(
        public sub(a:int, b:int) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test04");
        auto result = jit->Execute<double, int64_t, int64_t>("sub", 300, 141);
        Equal<double>(result, 159);
    }

    /**
     * Test subtract a double from integer and returns integer
     **/
    void TEST05()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:double) : int {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test05");
        });

        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 10);
    }

    /**
     * Test subtract a double from integer and returns integer through casting
     **/
    void TEST06()
    {
        const std::string source = R"source(
        public sub(a:int, b:double) : int {
            return (int a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test06");
        auto result = jit->Execute<int64_t, int64_t, double>("sub", 10, 1.2);
        Equal<int64_t>(result, 8);
    }

    /**
     * Test subtract double from integer and return double
     **/
    void TEST07()
    {
        const std::string source = R"source(
        public sub(a:int, b:double) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test07");
        auto result = jit->Execute<double, int64_t, double> ("sub", 4, 1.6);
        DoubleEqual(result, 2.4);
        result = jit->Execute<double, int64_t, double> ("sub", 34, 3.4);
        DoubleEqual(result, 30.6);
        auto const a = rand();
        auto const b = rand() / 1.2;
        result = jit->Execute<double, int64_t, double> ("sub", a, b);
        DoubleEqual(result, a - b);
    }

    /**
     * Test subtract a double from an integer and try to return byte
     **/
    void TEST08()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:double) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test08");
        });

        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 13);
    }

    /**
     * Assert invalid cast by casting a double to byte
     **/
    void TEST09()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:double) : byte {
                return (byte a - b);
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test09");
        });

        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 15);
    }

    /**
     * Test subtract a byte from integer and return integer
     **/    
    void TEST10()
    {
        const std::string source = R"source(
        public sub(a:int, b:byte) : int {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test10");
        auto result = jit->Execute<int64_t, int64_t, uint8_t>("sub", 3456, 56);
        Equal<int64_t>(result, 3400);
        result = jit->Execute<int64_t, int64_t, uint8_t>("sub", 6, 56);
        Equal<int64_t>(result, -50);
    }

    /**
     * Test subtract a byte from integer and return a double
     **/
    void TEST11()
    {
        const std::string source = R"source(
        public sub(a:int, b:byte) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test11");
        auto result = jit->Execute<double, int64_t, uint8_t>("sub", 1024, 46);
        Equal<double>(result, 978);
    }

    /**
     * Test subtract a byte from integer and returns a byte
     **/
    void TEST12()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:int, b:byte) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test11");
        });
        auto error_code = ex.GetErrorNo();
        Equal<int>(error_code, 10);
    }

    /**
     * Test subtract a byte from an integer and returns as a byte through casting
     **/
    void TEST13()
    {
        const std::string source = R"source(
        public sub(a:int, b:byte) : byte {
            return (byte a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test13");
        auto result = jit->Execute<uint8_t, int64_t, uint8_t>("sub", 1024, 46);
        Equal<int>(result, 210);
    }

    /**
     * Test subtract an integer from a double and return double
     **/
    void TEST14()
    {
        const std::string source = R"source(
        public sub(a:double, b:int) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test14");
        auto result = jit->Execute<double, double, int64_t>("sub", 10.24, 46);
        DoubleEqual(result, -35.76);
    }

    /**
     * Test subtract an integer from double and tires to return integer
     **/
    void TEST15()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:int) : int {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test15");
        });
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }

    /**
     * Test subtract an integer from double and tires to return integer through casting
     **/
    void TEST16()
    {
        const std::string source = R"source(
        public sub(a:double, b:int) : int {
            return (int a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test16");
        auto result = jit->Execute<int64_t, double, int64_t>("sub", 10.24, 46);
        Equal<int64_t>(result, -35);
    }

    /**
     * Test subtract an integer from double and tires to return byte
     **/
    void TEST17()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:int) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test17");
        });
        
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 13);
    }

    /**
     * Test subtract an integer from double and tires to return byte through casting
     **/
    void TEST18()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:int) : byte {
                return (byte a - b);
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test18");
        });
        
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 15);
    }

    /**
     * Test subtract a byte from a double and return double
     **/
    void TEST19()
    {
        const std::string source = R"source(
        public sub(a:double, b:byte) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test19");
        auto result = jit->Execute<double, double, int8_t>("sub", 10.24, 46);
        DoubleEqual(result, -35.76);
    }

    /**
     * Test subtract a byte from a double and return a integer
     **/
    void TEST20()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:byte) : int {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test20");
        });

        auto error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }

    /**
     * Test subtract a byte from a double and return a integer through casting
     **/
    void TEST21()
    {
        const std::string source = R"source(
        public sub(a:double, b:byte) : int {
            return (int a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test21");
        auto result = jit->Execute<int64_t, double, int8_t>("sub", 129.921, 127);
        Equal<int64_t>(result, 2);
    }

    /**
     * Test subtract a byte from a double and return a byte
     **/
    void TEST22()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:byte) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test22");
        });

        auto error_code = ex.GetErrorNo();
        Equal(error_code, 13);
    }

    /**
     * Test subtract a byte from a double and return a byte through casting
     **/
    void TEST23()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:double, b:byte) : byte {
                return (byte a - b);
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test23");
        });

        auto error_code = ex.GetErrorNo();
        Equal(error_code, 15);
    }

    /**
     * Test subtract an integer from a byte and return int 
     **/
    void TEST24()
    {
        const std::string source = R"source(
        public sub(a:byte, b:int) : int {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test24");
        auto result = jit->Execute<int64_t, unsigned char, int64_t>("sub", 251, 117);
        Equal<int64_t>(result, 134);
        result = jit->Execute<int64_t, unsigned char, int64_t>("sub", 15, 2248);
        Equal<int64_t>(result, -2233);
    }

    /**
     * Test subtract an integer from a byte and return double
     **/
    void TEST25()
    {
        const std::string source = R"source(
        public sub(a:byte, b:int) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test25");
        auto result = jit->Execute<double, unsigned char, int64_t>("sub", 252, 119);
        DoubleEqual(result, 133);
    }

    /**
     * Test subtract an integer from a byte and return byte
     **/
    void TEST26()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:byte, b:int) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test26");
        });
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }

    /**
     * Test subtract an integer from a byte and return byte through casting
     **/
    void TEST27()
    {
        const std::string source = R"source(
        public sub(a:byte, b:int) : byte {
            return (byte a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test27");
        auto result = jit->Execute<unsigned char, unsigned char, int64_t>("sub", 200, 147);
        Equal<unsigned char>(result, 53);
    }

    /**
     * Test subtract a double from a byte and return integer
     **/
    void TEST28()
    {
        auto ex = Throws<EmitterException>([] () {
            const std::string source = R"source(
            public sub(a:byte, b:double) : int {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test28");
        });
        auto error_code = ex.GetErrorNo();
        Equal(error_code, 10);
    }

    /**
     * Test subtract a double from a byte and return integer through casting
     **/
    void TEST29()
    {
        const std::string source = R"source(
        public sub(a:byte, b:double) : int {
            return (int a - b);
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test29");
        auto result = jit->Execute<int64_t, unsigned char, double>("sub", 20, 147.1);
        Equal<unsigned char>(result, -127);
    }

    /**
     * Test subtract a double from a byte and return a double
     **/
    void TEST30()
    {
        const std::string source = R"source(
        public sub(a:byte, b:double) : double {
            return a - b;
        }
        )source";
        auto jit = std::move(* HooJIT::Create());
        jit->Evaluate(source, "test30");
        auto result = jit->Execute<double, unsigned char, double>("sub", 21, 147.1);
        DoubleEqual(result, -126.1);
    }

    /**
     * Test subtract a double from a byte and return byte
     **/
    void TEST31()
    {
        auto ex = Throws<EmitterException>([] ()
        {
            const std::string source = R"source(
            public sub(a:byte, b:double) : byte {
                return a - b;
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test31");
        });

        auto error_code = ex.GetErrorNo();
        Equal(error_code, 13);
    }

    /**
     * Test subtract a double from a byte and return byte through casting
     **/
    void TEST32()
    {
        auto ex = Throws<EmitterException>([] ()
        {
            const std::string source = R"source(
            public sub(a:byte, b:double) : byte {
                return (byte a - b);
            }
            )source";
            auto jit = std::move(* HooJIT::Create());
            jit->Evaluate(source, "test31");
        });

        auto error_code = ex.GetErrorNo();
        Equal(error_code, 15);
    }
    
};

HOO_TEST_CASE(SubMethodTest)
