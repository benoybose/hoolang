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

#ifndef HOOLANG_X64EMITTER_HH
#define HOOLANG_X64EMITTER_HH

#include <ast/FunctionDefinition.hh>
#include <emitter/Emitter.hh>
#include <emitter/x86/EncoderX64.hh>
#include <ast/VariableDeclaration.hh>

#include <list>

using namespace hooc::ast;

namespace hooc {
    namespace emitter {
        namespace x86 {
            namespace win {
                class X64Emitter : public Emitter {
                private:
                    EncoderX64 _encoder;
                public:
                    explicit X64Emitter(const Unit *unit);

                public:
                    std::list<Code *> GenerateCode() override;
                };
            }
        }
    }
}

#endif //HOOLANG_X64EMITTER_HH
