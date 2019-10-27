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

#include <misc/Utility.hh>
#include <boost/test/unit_test.hpp>

#include <cstdint>

using namespace hooc::misc;

BOOST_AUTO_TEST_SUITE(UtilityTest)

    BOOST_AUTO_TEST_CASE(UtilityTest_GetBytes_1) {
        auto bytes = Utility::GetBytes(0x00000000000000A1);
        BOOST_CHECK_EQUAL(1, bytes.size());
        BOOST_CHECK_EQUAL(0xA1, bytes[0]);

        bytes = Utility::GetBytes(0x000000000000B2A1);
        BOOST_CHECK_EQUAL(2, bytes.size());
        BOOST_CHECK_EQUAL(0xA1, bytes[0]);
        BOOST_CHECK_EQUAL(0xB2, bytes[1]);

        bytes = Utility::GetBytes(0x000000003C00B2A1);
        BOOST_CHECK_EQUAL(4, bytes.size());
        BOOST_CHECK_EQUAL(0xA1, bytes[0]);
        BOOST_CHECK_EQUAL(0xB2, bytes[1]);
        BOOST_CHECK_EQUAL(0x00, bytes[2]);
        BOOST_CHECK_EQUAL(0x3C, bytes[3]);

        bytes = Utility::GetBytes(0x110000003C00B2A1);
        BOOST_CHECK_EQUAL(8, bytes.size());
        BOOST_CHECK_EQUAL(0xA1, bytes[0]);
        BOOST_CHECK_EQUAL(0xB2, bytes[1]);
        BOOST_CHECK_EQUAL(0x00, bytes[2]);
        BOOST_CHECK_EQUAL(0x3C, bytes[3]);
        BOOST_CHECK_EQUAL(0x00, bytes[4]);
        BOOST_CHECK_EQUAL(0x00, bytes[5]);
        BOOST_CHECK_EQUAL(0x00, bytes[6]);
        BOOST_CHECK_EQUAL(0x11, bytes[7]);

        bytes = Utility::GetBytes(0x0000000000000000);
        BOOST_CHECK_EQUAL(1, bytes.size());
        BOOST_CHECK_EQUAL(0x00, bytes[0]);

        bytes = Utility::GetBytes(0x001);
        BOOST_CHECK_EQUAL(1, bytes.size());
        BOOST_CHECK_EQUAL(0x01, bytes[0]);
    }

    BOOST_AUTO_TEST_CASE(Hex1) {
        auto result = Utility::ToHex(0x2F);
        BOOST_ASSERT("0x2F" == result);
    }

    BOOST_AUTO_TEST_CASE(Hex2) {
        auto result = Utility::ToHex(0x10);
        BOOST_ASSERT("0x10" == result);
    }

    BOOST_AUTO_TEST_CASE(Hex3) {
        auto result = Utility::ToHex(0x0);
        BOOST_ASSERT("0x00" == result);
    }

    BOOST_AUTO_TEST_CASE(Hex4) {
        auto result = Utility::ToHex(0x1);
        BOOST_ASSERT("0x01" == result);
    }

    BOOST_AUTO_TEST_CASE(Hex5) {
        auto result = Utility::ToHex(0xFF);
        BOOST_ASSERT("0xFF" == result);
    }

BOOST_AUTO_TEST_SUITE_END()

