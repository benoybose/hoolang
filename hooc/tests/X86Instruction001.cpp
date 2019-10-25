/*
 * Copyright 2019 Benoy Bose
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

#include <emitter/x86/X86Instruction.hh>
#include <emitter/x86/X86Definitions.hh>
#include <boost/test/unit_test.hpp>

using namespace hooc::emitter::x86;

BOOST_AUTO_TEST_SUITE(X86Instruction001)

    BOOST_AUTO_TEST_CASE(TEST01) {
        X86Instruction push(X86_OPCODE_PUSH_REGISTER);
        BOOST_CHECK_EQUAL(X86_PREFIX_INVALID, push.GetPrefix());
        BOOST_CHECK_EQUAL(X86_PREFIX_REX_INVALID, push.GetRexPrefix());
        BOOST_CHECK_EQUAL(X86_OPCODE_PUSH_REGISTER, push.GetOpcode());
        BOOST_CHECK_EQUAL(0, push.GetModRM());
        BOOST_CHECK_EQUAL(0, push.GetSIB());
        BOOST_CHECK_EQUAL(0, push.GetDisplacement());
        BOOST_CHECK_EQUAL(0, push.GetImmediate());
        push.AddRegister(X86_REG_RBP);
        BOOST_CHECK_EQUAL(0x55, push.GetOpcode());
    }

    BOOST_AUTO_TEST_CASE(TEST02) {
        X86Instruction push(X86_OPCODE_PUSH_REGISTER_RBP);
        BOOST_CHECK_EQUAL(X86_PREFIX_INVALID, push.GetPrefix());
        BOOST_CHECK_EQUAL(X86_PREFIX_REX_INVALID, push.GetRexPrefix());
        BOOST_CHECK_EQUAL(0x55, push.GetOpcode());
        BOOST_CHECK_EQUAL(0, push.GetModRM());
        BOOST_CHECK_EQUAL(0, push.GetSIB());
        BOOST_CHECK_EQUAL(0, push.GetDisplacement());
        BOOST_CHECK_EQUAL(0, push.GetImmediate());
    }

BOOST_AUTO_TEST_SUITE_END()