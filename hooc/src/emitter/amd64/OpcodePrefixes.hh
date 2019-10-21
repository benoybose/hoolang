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

#ifndef HOOLANG_OPCODEPREFIXES_HH
#define HOOLANG_OPCODEPREFIXES_HH

#include <cstdint>

namespace hooc {
    namespace emitter {
        namespace amd {
            const uint8_t PREFIX_LOCK = 0xF0;
            const uint8_t PREFIX_REPNE = 0xF2;
            const uint8_t PREFIX_REPNZ = 0xF2;
            const uint8_t PREFIX_REP = 0xF3;
            const uint8_t PREFIX_REPE = 0xF3;
            const uint8_t PREFIX_REPZ = 0xF3;

            const uint8_t PREFIX_SEGMENT_CS = 0x2E;
            const uint8_t PREFIX_SEGMENT_SS = 0x36;
            const uint8_t PREFIX_SEGMENT_DS = 0x3E;
            const uint8_t PREFIX_SEGMENT_ES = 0x26;
            const uint8_t PREFIX_SEGMENT_FS = 0x64;
            const uint8_t PREFIX_SEGMENT_GS = 0x65;
            const uint8_t PREFIX_BRANCH_NOT_TAKEN = 0x2E;
            const uint8_t PREFIX_BRANCH_TAKEN = 0x3E;

            const uint8_t PREFIX_OPERAND_SIZE_OVERRIDE = 0x66;
            const uint8_t PREFIX_ADDRESS_SIZE_OVERRIDE = 0x67;
        }
    }
}

#endif //HOOLANG_OPCODEPREFIXES_HH
