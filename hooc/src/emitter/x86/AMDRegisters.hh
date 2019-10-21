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

#ifndef HOOLANG_AMDREGISTERS_HH
#define HOOLANG_AMDREGISTERS_HH

#include <cstdint>

namespace hooc {
    namespace emitter {
        namespace x86 {
            const uint8_t REG_AL = 0;
            const uint8_t REG_BL = 3;
            const uint8_t REG_CL = 1;
            const uint8_t REG_DL = 2;
            const uint8_t REG_AH = 4;
            const uint8_t REG_BH = 7;
            const uint8_t REG_CH = 5;
            const uint8_t REG_DH = 6;

            const uint8_t REG_AX = 0;
            const uint8_t REG_BX = 3;
            const uint8_t REG_CX = 1;
            const uint8_t REG_DX = 2;

            const uint8_t REG_EAX = 0;
            const uint8_t REG_EBX = 3;
            const uint8_t REG_ECX = 1;
            const uint8_t REG_EDX = 2;

            const uint8_t REG_RAX = 0;
            const uint8_t REG_RBX = 3;
            const uint8_t REG_RCX = 1;
            const uint8_t REG_RDX = 2;

            const uint8_t REG_SP = 4;
            const uint8_t REG_BP = 5;
            const uint8_t REG_SI = 6;
            const uint8_t REG_DI = 7;

            const uint8_t REG_ESP = 4;
            const uint8_t REG_EBP = 5;
            const uint8_t REG_ESI = 6;
            const uint8_t REG_EDI = 7;

            const uint8_t REG_RBP = 5;
            const uint8_t REG_RSP = 4;
            const uint8_t REG_RSI = 6;
            const uint8_t REG_RDI = 7;

            const uint8_t REG_R8 = 8;
            const uint8_t REG_R9 = 9;
            const uint8_t REG_R10 = 10;
            const uint8_t REG_R11 = 11;
            const uint8_t REG_R12 = 12;
            const uint8_t REG_R13 = 13;
            const uint8_t REG_R14 = 14;
            const uint8_t REG_R15 = 15;
        }
    }
}

#endif //HOOLANG_AMDREGISTERS_HH
