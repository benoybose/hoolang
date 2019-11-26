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

#ifndef HOOLANG_X86FUNCEMITTER_HH
#define HOOLANG_X86FUNCEMITTER_HH

#include <ast/Statement.hh>
#include <emitter/StackItem.hh>
#include <emitter/FuncEmitter.hh>
#include <emitter/FuncEmitterContext.hh>
#include <emitter/x86/X86Encoder.hh>
#include <cstdint>

using namespace std;

namespace hooc {
    namespace emitter {
        namespace x86 {
            class X86FuncEmitter : public FuncEmitter {
            private:
                X86Encoder _encoder;

            public:
                X86FuncEmitter(FunctionDefinition *definition, const EmitterConfig &config);

            public:
                Code *GenerateCode() override;

            protected:
                FuncEmitterContext *CreateFunctionEmitterContext();

            private:
                void ProcessArguments(const std::list<VariableDeclaration *> &arguments, 
                                      byte_vector &header,
                                      byte_vector &footer);
                void MapArgsToStack(StackItemSet &stack_items, 
                                        const std::list<VariableDeclaration *> &args);
                void MapArgsToStack(StackItemSet &stack_items,
                                        const std::list<VariableDeclaration *> &args, 
                                        int8_t start,
                                        int8_t offset);
                size_t MapVarsToStack(StackItemSet &stack_items, const Statement* body, 
                                        int8_t position,
                                        int8_t offset, 
                                        int8_t depth_offset,
                                        int8_t align_by);
                size_t MapVarsToStack(StackItemSet &stack_items, const Statement* body);
                void SaveArgumentsWin64(const std::list<VariableDeclaration *> &arguments,
                                        byte_vector &header);
                void SaveArgumentsLinux64(const std::list<VariableDeclaration *> &arguments,
                                        byte_vector &header);
                bool IsDouble(VariableDeclaration *arg1);                
            };
        }
    }
}

#endif //HOOLANG_X86FUNCEMITTER_HH
