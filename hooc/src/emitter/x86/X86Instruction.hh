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

#ifndef HOOLANG_X86INSTRUCTION_HH
#define HOOLANG_X86INSTRUCTION_HH

#include <emitter/x86/X86Definitions.hh>

#include <cstdint>
#include <stdint-gcc.h>
#include "Encoder.hh"

using namespace std;

namespace hooc {
    namespace emitter {
        namespace x86 {
            extern const uint64_t X86_OPCODE_NOP;
            extern const uint64_t X86_OPCODE_PUSH_REGISTER;
            extern const uint64_t X86_OPCODE_PUSH_REGISTER_RBP;
            extern const uint64_t X86_OPCODE_MOV_REGMEM64_REG64;
            extern const uint64_t X86_OPCODE_RET;
            extern const uint64_t X86_OPCODE_RET_INTER_SEGMENT;
            extern const uint64_t X86_OPCODE_POP_REGISTER;

            /**
             * Move scalar double-precision floating-point value from xmm2 register to xmm1/m64.
             */
            extern const uint64_t X86_OPCODE_MOVSD_XMM1MEM64_XMM2;

            class X86Instruction {
            private:
                uint8_t _prefix;
                uint8_t _rex_prefix;
                uint32_t _opcode;
                uint8_t _mod_r_m;
                uint8_t _s_i_b;
                uint32_t _displacement;
                uint32_t _immediate;
            public:
                X86Instruction();
                X86Instruction(X86RexPrefix rex_prefix, uint32_t opcode);
                X86Instruction(X86OpcodePrefix prefix, uint32_t opcode);
                explicit X86Instruction(uint32_t opcode);
                X86Instruction(X86OpcodePrefix prefix, X86RexPrefix rex_prefix, uint32_t opcode);

            public:
                uint8_t GetPrefix() const;

                uint8_t GetRexPrefix() const;

                uint32_t GetOpcode() const;

                uint8_t GetModRM() const;

                uint8_t GetSIB() const;

                uint32_t GetDisplacement() const;

                uint32_t GetImmediate() const;

            public:
                void AddRegister(X86RegisterType reg);
                void SetOperands(X86RegisterType reg_from, X86RegisterType reg_to);
                void SetOperands(X86RegisterType reg_from,
                                 X86RegisterType reg_to, uint8_t disp8);

            public:
                byte_vector Encode();

            public:
                static bool IsRegFieldExtendedInModRM(X86RegisterType reg);
            };
        }
    }
}


#endif //HOOLANG_X86INSTRUCTION_HH
