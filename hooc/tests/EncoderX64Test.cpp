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
#include <emitter/x86/X86Encoder.hh>

using namespace hooc::emitter::x86;

BOOST_AUTO_TEST_SUITE(Encoder64Test)

    BOOST_AUTO_TEST_CASE(TEST01) {
        X86Encoder encoder;
        auto bytes = encoder.PUSH(X86_REG_RBP);
        byte expected[1] = {0x55};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 1));
    }

    BOOST_AUTO_TEST_CASE(TEST02) {
        X86Encoder encoder;
        auto bytes = encoder.MOV(X86_REG_RSP, X86_REG_RBP);
        byte expected[3] = {0x48, 0x89, 0xE5};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 3));
    }

    BOOST_AUTO_TEST_CASE(TEST03) {
        X86Encoder encoder;
        auto bytes = encoder.MOV(X86_REG_RCX, X86_REG_RBP, 0x10);
        byte expected[4] = {0x48, 0x89, 0x4d, 0x10};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 4));
    }

    BOOST_AUTO_TEST_CASE(TEST04) {
        X86Encoder encoder;
        auto bytes = encoder.MOV(X86_REG_RDX, X86_REG_RBP, 0x18);
        byte expected[4] = {0x48, 0x89, 0x55, 0x18};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 4));
    }

    BOOST_AUTO_TEST_CASE(TEST05) {
        X86Encoder encoder;
        auto bytes = encoder.RET(true);
        byte expected[1] = {0xCB};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 1));
    }

    BOOST_AUTO_TEST_CASE(TEST06) {
        X86Encoder encoder;
        auto bytes = encoder.RET(false);
        byte expected[1] = {0xC3};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 1));
    }

    BOOST_AUTO_TEST_CASE(TEST07) {
        X86Encoder encoder;
        auto bytes = encoder.POP(X86_REG_RBP);
        byte expected[1] = {0x5D};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 1));
    }

    BOOST_AUTO_TEST_CASE(TEST08) {
        X86Encoder encoder;
        auto bytes = encoder.NOP();
        byte expected[1] = {0x90};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 1));
    }

    BOOST_AUTO_TEST_CASE(TEST09) {
        X86Encoder encoder;
        auto bytes = encoder.MOV(X86_REG_R8, X86_REG_RBP, 0x20);
        byte expected[4] = {0x4c, 0x89, 0x45, 0x20};
        BOOST_CHECK(VerifyByteVector(bytes, expected, 4));
    }

    BOOST_AUTO_TEST_CASE(TEST11) {
        X86Encoder encoder;
        auto bytes = encoder.MOVSD(X86_REG_XMM0, X86_REG_RBP, 0x10);
        byte expected[5] = { 0xf2, 0x0f, 0x11, 0x45, 0x10 };
        BOOST_CHECK(VerifyByteVector(bytes, expected, 5));
    }

    BOOST_AUTO_TEST_CASE(TEST12) {
        X86Encoder encoder;
        auto bytes = encoder.MOVSD(X86_REG_XMM1, X86_REG_RBP, 0x18);
        byte expected[5] = { 0xf2, 0x0f, 0x11, 0x4d, 0x18 };
        BOOST_CHECK(VerifyByteVector(bytes, expected, 5));
    }

    BOOST_AUTO_TEST_CASE(TEST13) {
        X86Encoder encoder;
        auto bytes = encoder.MOVSD(X86_REG_XMM2, X86_REG_RBP, 0x20);
        byte expected[5] = { 0xf2, 0x0f, 0x11, 0x55, 0x20 };
        BOOST_CHECK(VerifyByteVector(bytes, expected, 5));
    }

    BOOST_AUTO_TEST_CASE(TEST14) {
        X86Encoder encoder;
        auto bytes = encoder.MOVSD(X86_REG_XMM3, X86_REG_RBP, 0x28);
        byte expected[5] = { 0xf2, 0x0f, 0x11, 0x5d, 0x28 };
        BOOST_CHECK(VerifyByteVector(bytes, expected, 5));
    }

BOOST_AUTO_TEST_SUITE_END()