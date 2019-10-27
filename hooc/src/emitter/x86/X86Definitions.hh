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

#ifndef HOOLANG_X86DEFINITIONS_HH
#define HOOLANG_X86DEFINITIONS_HH

#include <emitter/EmitterDefinitions.hh>

#include <cstdint>
#include <vector>

namespace hooc {
    namespace emitter {
        namespace x86 {

            typedef enum {
                X86_PREFIX_INVALID = 0x00,
                X86_PREFIX_G1_LOCK = 0xF0,
                X86_PREFIX_G1_REPN = 0xF2, // REPNE, REPNZ
                X86_PREFIX_G1_REP = 0xF3, // REP, REPE, REPZ
                X86_PREFIX_G2_SEGMENT_CS = 0x2E,
                X86_PREFIX_G2_SEGMENT_SS = 0x36,
                X86_PREFIX_G2_SEGMENT_DS = 0x3E,
                X86_PREFIX_G2_SEGMENT_ES = 0x26,
                X86_PREFIX_G2_SEGMENT_FS = 0x64,
                X86_PREFIX_G2_SEGMENT_GS = 0x65,
                X86_PREFIX_G2_BRANCH_NOT_TAKEN = 0x2E,
                X86_PREFIX_G2_BRANCH_TAKEN = 0x3E,
                X86_PREFIX_G3_OPERAND_SIZE_OVERRIDE = 0x66,
                X86_PREFIX_G4_ADDRESS_SIZE_OVERRIDE = 0x67
            } X86OpcodePrefix;

            typedef enum {
                X86_PREFIX_REX_INVALID = 0x00,
                X86_PREFIX_REX_W = 0x48, // When 1, a 64-bit operand size is used. Otherwise, when 0, the default operand size is used
                X86_PREFIX_REX_R = 0x44, // This 1-bit value is an extension to the MODRM.reg field
                X86_PREFIX_REX_X = 0x42, // This 1-bit value is an extension to the SIB.index field
                X86_PREFIX_REX_B = 0x41  // This 1-bit value is an extension to the MODRM.rm field or the SIB.base field
            } X86RexPrefix;

            typedef enum {
                X86_REG_INVALID = -1,
                X86_REG_RAX = 0,
                X86_REG_RCX = 1,
                X86_REG_RBX = 3,
                X86_REG_RDX = 2,
                X86_REG_RSP = 4,
                X86_REG_RBP = 5,
                X86_REG_RSI = 6,
                X86_REG_RDI = 7,
                X86_REG_R8 = 8,
                X86_REG_R9 = 9,
                X86_REG_R10 = 10,
                X86_REG_R11 = 11,
                X86_REG_R12 = 12,
                X86_REG_R13 = 13,
                X86_REG_R14 = 14,
                X86_REG_R15 = 15,
                X86_REG_AH = 4,
                X86_REG_BH = 7,
                X86_REG_CH = 5,
                X86_REG_DH = 6
            } X86RegisterType;

            typedef enum {
                X86_MOD_EFFECTIVE = 0x00,
                X86_MOD_EFFECTIVE_DISP8 = 0x40,
                X86_MOD_EFFECTIVE_DISP32 = 0x80,
                X86_MOD_DIRECT = 0xC0
            } X86InstructionMode;
        }
    }
}

#endif //HOOLANG_X86DEFINITIONS_HH
