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

#ifndef HOOLANG_X64ENCODER_HH
#define HOOLANG_X64ENCODER_HH

#include <emitter/x86/X86Definitions.hh>
#include <emitter/x86/Encoder.hh>
#include <cstdint>
#include <vector>
#include <cstdint>

namespace hooc {
    namespace emitter {
        namespace x86 {
            class X64Encoder: public Encoder {
            public:
                byte_vector PUSH(X86RegisterType reg) override;
                byte_vector MOV(X86RegisterType reg_from, X86RegisterType reg_to) override;
                byte_vector MOV(X86RegisterType reg_from,
                        X86RegisterType reg_to,
                        uint8_t disp8) override;
                byte_vector RET(bool inter_segment) override;

                byte_vector POP(X86RegisterType reg) override;

                byte_vector MOVSD(X86RegisterType reg_from, X86RegisterType reg_to, uint8_t disp8) override;
            };
        }
    }
}


#endif //HOOLANG_X64ENCODER_HH
