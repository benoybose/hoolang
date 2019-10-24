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

#include "X86Instruction.hh"

namespace hooc {
    namespace emitter {
        namespace x86 {
            X86Instruction::X86Instruction(X86OpcodePrefix prefix,
                                           X86RexPrefix rex_prefix,
                                           uint32_t opcode) : _prefix(prefix),
                                                              _rex_prefix(rex_prefix),
                                                              _opcode(opcode) {

            }

            X86OpcodePrefix X86Instruction::GetPrefix() const {
                return _prefix;
            }

            X86RexPrefix X86Instruction::GetRexPrefix() const {
                return _rex_prefix;
            }

            uint32_t X86Instruction::GetOpcode() const {
                return _opcode;
            }

            uint8_t X86Instruction::GetModRM() const {
                return _mod_r_m;
            }

            uint8_t X86Instruction::GetSIB() const {
                return _s_i_b;
            }

            uint32_t X86Instruction::GetDisplacement() const {
                return _displacement;
            }

            uint32_t X86Instruction::GetImmediate() const {
                return _immediate;
            }
        }
    }
}
