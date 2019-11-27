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
#include <misc/Utility.hh>

#include <boost/test/unit_test.hpp>
#include <cstdint>

using namespace hooc::misc;
using namespace std;

bool VerifyByteVector(const byte_vector &vector, uint8_t *bytes, size_t size) {
    BOOST_CHECK(vector.size() == size);
    if (vector.size() != size) {
        return false;
    }

    for (size_t index = 0; index < size; index++) {
        BOOST_CHECK_MESSAGE(vector[index] == bytes[index],
                            "[" << index << "] (" << Utility::ToHex(vector[index]) << " == "
                                << Utility::ToHex(bytes[index]) << ")");
        if (vector[index] != bytes[index]) {
            return false;
        }
    }
    return true;
}

bool VerifyFuncCode(Code *code, const std::string &name, uint8_t *expected_buffer, size_t size) {
    if(CODE_TYPE_FUNCTION != code->GetType()) {
        return false;
    }
    if (name != code->GetName()) {
        return false;
    }
    const auto &buffer = code->GetBuffer();
    if (size != buffer.size()) {
        return false;
    }
    return VerifyByteVector(buffer, expected_buffer, size);
}
