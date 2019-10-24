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

#include "EncoderX64.hh"

namespace hooc {
    namespace emitter {
        namespace x86 {
            std::vector<uint8_t> EncoderX64::PUSH(X86RegisterType reg) {
                std::vector<uint8_t> ins;
                uint8_t opcode = 0x50 + reg; // 50+rd
                ins.push_back(opcode);
                return ins;
            }

            std::vector<uint8_t> EncoderX64::MOV(X86RegisterType reg64_from, X86RegisterType reg64_to) {
                std::vector<uint8_t> ins;
                ins.push_back(0x48); // REX prefix for 64 bit operands
                ins.push_back(0x89); // Opcode for MOV

                uint8_t mod_r_m = 0x03;
                mod_r_m <<= 6; // ModR/M register direct addressing model. Bits 7, 6
                mod_r_m += (reg64_from << 3); // Setting source register to reg bit field. Bits 5, 4, 3
                mod_r_m += reg64_to; // Setting destination register to rm bit field. Bits 2, 1, 0
                ins.push_back(mod_r_m);
                return ins;
            }
        }
    }
}
