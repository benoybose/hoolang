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

#ifndef HOOLANG_ENCODER_HH
#define HOOLANG_ENCODER_HH

#include <emitter/x86/X86Definitions.hh>

#include <cstdint>
#include <vector>

namespace hooc {
    namespace emitter {
        namespace x86 {
            class Encoder {
            public:
                virtual byte_vector PUSH(X86RegisterType reg) = 0;
                virtual byte_vector MOV(X86RegisterType reg64_from, X86RegisterType reg64_to) = 0;
                virtual byte_vector MOV(X86RegisterType reg_from, X86RegisterType reg_to, uint8_t displacement) = 0;
                virtual byte_vector RET(bool inter_segment) = 0;
                virtual byte_vector POP(X86RegisterType reg) = 0;
            };
        }
    }
}


#endif //HOOLANG_ENCODER_HH
