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

#include "HoocTestHelper.hh"

#include <boost/test/unit_test.hpp>
#include <emitter/x86/X86Definitions.hh>
#include <emitter/x86/EncoderX64.hh>

using namespace hooc::emitter::x86;

BOOST_AUTO_TEST_SUITE(Encoder64Test)

    BOOST_AUTO_TEST_CASE(TEST01) {
        EncoderX64 encoder;
        auto bytes = encoder.PUSH(X86_REG_RBP);
        byte expected[1] = {0x55};
        BOOST_ASSERT(VerifyByteVector(bytes, expected, 1));
    }

    BOOST_AUTO_TEST_CASE(TEST02) {
        EncoderX64 encoder;
        auto bytes = encoder.MOV(X86_REG_RSP, X86_REG_RBP);
        byte expected[3] = {0x48, 0x89, 0xE5};
        BOOST_ASSERT(VerifyByteVector(bytes, expected, 3));
    }

    BOOST_AUTO_TEST_CASE(TEST03) {
        EncoderX64 encoder;
        auto bytes = encoder.MOV(X86_REG_RCX, X86_REG_RBP, 0x10);
        byte expected[4] = {0x48, 0x89, 0x4d, 0x10};
        BOOST_ASSERT(VerifyByteVector(bytes, expected, 4));
    }

    BOOST_AUTO_TEST_CASE(TEST04) {
        EncoderX64 encoder;
        auto bytes = encoder.MOV(X86_REG_RDX, X86_REG_RBP, 0x18);
        byte expected[4] = {0x48, 0x89, 0x55, 0x18};
        BOOST_ASSERT(VerifyByteVector(bytes, expected, 4));
    }

    BOOST_AUTO_TEST_CASE(TEST05) {
        EncoderX64 encoder;
        auto bytes = encoder.RET(true);
        byte expected[1] = { 0xCB };
        BOOST_ASSERT(VerifyByteVector(bytes, expected, 1));
    }

BOOST_AUTO_TEST_SUITE_END()