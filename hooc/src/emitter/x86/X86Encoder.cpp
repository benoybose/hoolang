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

#include "X86Encoder.hh"
#include "X86Instruction.hh"

namespace hooc {
    namespace emitter {
        namespace x86 {
            byte_vector X86Encoder::PUSH(X86RegisterType reg) {
                X86Instruction instruction(X86_OPCODE_PUSH_REGISTER);
                instruction.AddRegister(reg);
                byte_vector vector = instruction.Encode();
                return vector;
            }

            byte_vector X86Encoder::MOV(X86RegisterType reg_from,
                                        X86RegisterType reg_to) {
                X86Instruction instruction(X86_PREFIX_REX_W, X86_OPCODE_MOV_REGMEM64_REG64);
                instruction.SetOperands(reg_from, reg_to);
                byte_vector vector = instruction.Encode();
                return vector;
            }

            byte_vector X86Encoder::MOV(X86RegisterType reg_from,
                                        X86RegisterType reg_to,
                                        int8_t disp8) {
                X86Instruction instruction(X86_PREFIX_REX_W, X86_OPCODE_MOV_REGMEM64_REG64);
                instruction.SetOperands(reg_from, reg_to, disp8);
                byte_vector vector = instruction.Encode();
                return vector;
            }

            byte_vector X86Encoder::RET(bool inter_segment) {
                if (inter_segment) {
                    X86Instruction instruction(X86_OPCODE_RET_INTER_SEGMENT);
                    return instruction.Encode();
                } else {
                    X86Instruction instruction(X86_OPCODE_RET);
                    return instruction.Encode();
                }
            }

            byte_vector X86Encoder::POP(X86RegisterType reg) {
                X86Instruction instruction(X86_OPCODE_POP_REGISTER);
                instruction.AddRegister(reg);
                return instruction.Encode();
            }

            byte_vector X86Encoder::MOVSD(X86RegisterType reg_from,
                                          X86RegisterType reg_to,
                                          int8_t disp8) {
                X86Instruction instruction(X86_OPCODE_MOVSD_XMM1MEM64_XMM2);
                instruction.SetOperands(reg_from, reg_to, disp8);
                return instruction.Encode();
            }

            byte_vector X86Encoder::NOP() {
                X86Instruction instruction;
                return instruction.Encode();
            }
        }
    }
}