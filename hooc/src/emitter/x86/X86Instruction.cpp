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

#include <misc/Utility.hh>
#include "X86Instruction.hh"

using namespace hooc::misc;

namespace hooc {
    namespace emitter {
        namespace x86 {

            const uint64_t X86_OPCODE_PUSH_REGISTER = 0x50;
            const uint64_t X86_OPCODE_PUSH_REGISTER_RBP = 0x55;
            const uint64_t X86_OPCODE_MOV_REGMEM64_REG64 = 0x89;

            X86Instruction::X86Instruction() :
                    _prefix(X86_PREFIX_INVALID),
                    _rex_prefix(X86_PREFIX_REX_INVALID),
                    _opcode(0x90),
                    _mod_r_m(0),
                    _s_i_b(0),
                    _displacement(0),
                    _immediate(0) {

            }

            X86Instruction::X86Instruction(X86RexPrefix rex_prefix, uint32_t opcode) :
                    X86Instruction() {
                this->_rex_prefix = rex_prefix;
                this->_opcode = opcode;
            }

            X86Instruction::X86Instruction(X86OpcodePrefix prefix, uint32_t opcode) :
                    X86Instruction() {
                this->_prefix = prefix;
                this->_opcode = opcode;
            }

            X86Instruction::X86Instruction(uint32_t opcode) :
                    X86Instruction() {
                this->_opcode = opcode;
                if(0 == this->_opcode) {
                    this->_opcode = 0x90;
                }
            }

            X86Instruction::X86Instruction(X86OpcodePrefix prefix,
                                           X86RexPrefix rex_prefix,
                                           uint32_t opcode) : X86Instruction() {
                this->_prefix = prefix;
                this->_rex_prefix = rex_prefix;
                this->_opcode = opcode;
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

            void X86Instruction::AddRegister(X86RegisterType reg) {
                if(X86_REG_INVALID == reg) {
                    return;
                }

                this->_opcode |= reg;
            }

            void X86Instruction::SetOperands(X86RegisterType reg) {
                this->_mod_r_m = X86_MOD_EFFECTIVE;
                this->_mod_r_m |= (reg << 3);
            }

            void X86Instruction::SetOperands(X86RegisterType reg,
                    uint8_t displacement) {
                this->_mod_r_m = X86_MOD_EFFECTIVE_DISP8;
                this->_mod_r_m |= reg << 3;
                this->_displacement = displacement;
            }

            void X86Instruction::SetOperands(X86RegisterType reg,
                    uint32_t displacement) {
                this->_mod_r_m = X86_MOD_EFFECTIVE_DISP32;
                this->_mod_r_m |= reg << 3;
                this->_displacement = displacement;
            }

            void X86Instruction::SetOperands(X86RegisterType reg1,
                    X86RegisterType reg2) {
                this->_mod_r_m = X86_MOD_DIRECT;
                this->_mod_r_m |= reg1 << 3;
                this->_mod_r_m |= reg2;
            }

            byte_vector X86Instruction::Encode() {
                byte_vector data;
                if (0 != this->_prefix) {
                    auto prefix = (byte) this->_prefix;
                    data.push_back(prefix);
                }

                if (0 != this->_rex_prefix) {
                    auto rex_prefix = this->_rex_prefix;
                    data.push_back(rex_prefix);
                }

                if (0 == this->_opcode) {
                    data.push_back(0x90);
                } else {
                    auto bytes = Utility::GetBytes(this->_opcode);
                    for (auto b: bytes) {
                        data.push_back(b);
                    }
                }

                if (0 != this->_mod_r_m) {
                    data.push_back(this->_mod_r_m);
                }

                if (0 != this->_s_i_b) {
                    data.push_back(this->_s_i_b);
                }

                if (0 != this->_displacement) {
                    auto bytes = Utility::GetBytes(this->_displacement);
                    data.insert(data.end(), bytes.begin(), bytes.end());
                }

                if (0 != this->_immediate) {
                    auto bytes = Utility::GetBytes(this->_immediate);
                    data.insert(data.end(), bytes.begin(), bytes.end());
                }
                return data;
            }
        }
    }
}
