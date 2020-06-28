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

#include "Utility.hh"

#include <cstdint>
#include <vector>
#include <cstdint>

using namespace std;

namespace hooc {
    namespace misc {

        const char UTILITY_HEX_DIGITS[16] = {
                '0', '1', '2', '3',
                '4', '5', '6', '7',
                '8', '9', 'A', 'B',
                'C', 'D', 'E', 'F' };
        const char UTILITY_HEX_BASE = 16;

        vector<uint8_t> Utility::GetBytes(std::uint64_t value) {
            vector<uint8_t> bytes;
            bool started = false;

            for(size_t index = 0; index < 8; index++) {
                uint8_t shift_offset = 8 * (8 - (index + 1));
                uint64_t mask = 0x00000000000000FF << shift_offset; // NOLINT(hicpp-signed-bitwise)
                uint64_t masked_value = value & mask;
                masked_value >>= shift_offset;
                auto byte = (uint8_t) masked_value;
                if (!started) {
                    started = (0 < byte);
                }

                if(started) {
                    bytes.insert(bytes.begin(), byte);
                }
            }
            if(bytes.empty()) {
                bytes.push_back(0);
            }
            return bytes;
        }

        void Utility::AppendTo(std::vector<std::uint8_t> &to, const std::vector<std::uint8_t> &from) {
            to.insert(to.end(), from.begin(), from.end());
        }

        std::string Utility::ToHex(std::uint8_t byte) {
            std::string result;
            uint8_t quotient = byte;
            uint8_t reminder = 0;

            while(0 != quotient) {
                reminder = quotient % UTILITY_HEX_BASE;
                result.insert(result.begin(), UTILITY_HEX_DIGITS[reminder]);
                quotient = quotient / UTILITY_HEX_BASE;
            }

            if(result.empty()) {
                result = "00";
            } else if(1 == result.length()) {
                result.insert(result.begin(), '0');
            }

            result.insert(result.begin(), 'x');
            result.insert(result.begin(), '0');
            return result;
        }
    }
}
