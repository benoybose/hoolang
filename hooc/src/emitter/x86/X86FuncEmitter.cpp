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

#include "X86FuncEmitter.hh"
#include <emitter/FuncEmitterContext.hh>
#include <emitter/NameMangler.hh>
#include <ast/CompoundStatement.hh>
#include <ast/Statement.hh>
#include <ast/DeclarationStatement.hh>
#include <ast/Declaration.hh>
#include <ast/VariableDeclaration.hh>
#include <misc/Utility.hh>
#include <ast/BasicDataTypes.hh>
#include <ast/BasicDataTypeSpecification.hh>

using namespace hooc::ast;
using namespace hooc::misc;

namespace hooc {
    namespace emitter {
        namespace x86 {
            const size_t WIN_X64_REG_COUNT = 4;
            const X86RegisterType WIN_X64_ARG_DOUBLE_REGS[WIN_X64_REG_COUNT] = {
                    X86_REG_XMM0,
                    X86_REG_XMM1,
                    X86_REG_XMM2,
                    X86_REG_XMM3
            };
            const X86RegisterType WIN_X64_ARG_INT_REGS[WIN_X64_REG_COUNT] = {
                    X86_REG_RCX,
                    X86_REG_RDX,
                    X86_REG_R8,
                    X86_REG_R9
            };
            const size_t LINUX_X64_REG_COUNT = 6;
            const size_t LINUX_X64_FLOAT_REG_COUNT = 8;
            const X86RegisterType LINUX_X64_ARG_DOUBLE_REGS[LINUX_X64_FLOAT_REG_COUNT] = {
                X86_REG_XMM0,
                X86_REG_XMM1,
                X86_REG_XMM2,
                X86_REG_XMM3,
                X86_REG_XMM4,
                X86_REG_XMM5,
                X86_REG_XMM6,
                X86_REG_XMM7
            };
            const X86RegisterType LINUX_X64_ARG_INT_REGS[LINUX_X64_REG_COUNT] = {
                X86_REG_RDI,
                X86_REG_RSI,
                X86_REG_RDX,
                X86_REG_RCX,
                X86_REG_R8,
                X86_REG_R9
            };


            X86FuncEmitter::X86FuncEmitter(FunctionDefinition *definition, const EmitterConfig &config)
                    : FuncEmitter(definition, config) {
                auto context = this->CreateFunctionEmitterContext();
                this->SetFunctionContext(context);
            }

            FuncEmitterContext *X86FuncEmitter::CreateFunctionEmitterContext() {
                auto function_declaration = this->GetDefinition()->GetDeclaration();                
                StackItemSet stack_items;

                auto args = function_declaration->GetParamList();
                this->MapArgsToStack(stack_items, args);

                auto body = this->GetDefinition()->GetBody();
                auto depth = this->MapVarsToStack(stack_items, body);

                NameMangler mangler;
                auto name = mangler.Mangle(function_declaration);

                auto context = new FuncEmitterContext(depth, name);
                for (const auto &stack_item: stack_items) {
                    context->AddItem(stack_item);
                }
                return context;
            }

            Code *X86FuncEmitter::GenerateCode() {
                byte_vector header;
                byte_vector body;
                byte_vector footer;

                auto function_definition = this->GetDefinition();
                auto declaration = function_definition->GetDeclaration();
                const auto &arguments = declaration->GetParamList();
                ProcessArguments(arguments, header, footer);

                auto statement = function_definition->GetBody();
                if (STMT_COMPOUND == statement->GetStatementType()) {
                    auto compound_statement = (CompoundStatement *) statement;
                    if (compound_statement->GetStatements().empty()) {
                        auto ins_nop = this->_encoder.NOP();
                        Utility::AppendTo(body, ins_nop);
                    }
                }

                auto ins_return = this->_encoder.RET(false);
                Utility::AppendTo(footer, ins_return);

                auto name = this->GetMangler().Mangle(declaration);
                byte_vector buffer;
                Utility::AppendTo(buffer, header);
                Utility::AppendTo(buffer, body);
                Utility::AppendTo(buffer, footer);
                auto code = new Code(CODE_TYPE_FUNCTION, name, buffer);
                return code;
            }

            void X86FuncEmitter::ProcessArguments(const std::list<VariableDeclaration *> &arguments,
                                                  byte_vector &header, byte_vector &footer) {
                auto config = this->GetConfig();
                auto push_rbp = this->_encoder.PUSH(X86_REG_RBP);
                Utility::AppendTo(header, push_rbp);
                auto mov_rsp_rbp = this->_encoder.MOV(X86_REG_RSP, X86_REG_RBP);
                Utility::AppendTo(header, mov_rsp_rbp);

                auto pop_rbp = this->_encoder.POP(X86_REG_RBP);
                Utility::AppendTo(footer, pop_rbp);

                if (config == EMITTER_WIN64) {
                    SaveArgumentsWin64(arguments, header);
                } else if(config == EMITTER_LINUX64) {
                    SaveArgumentsLinux64(arguments, header);
                }
            }

            void X86FuncEmitter::MapArgsToStack(StackItemSet &stack_items, 
                                        const std::list<VariableDeclaration *> &args) {
                const auto &config = this->GetConfig();
                if(config == EMITTER_WIN64) {
                    this->MapArgsToStack(stack_items, args, 16, 8);
                } else if(config == EMITTER_LINUX64) {
                    this->MapArgsToStack(stack_items, args, -8, -8);
                }
            }

            void X86FuncEmitter::MapArgsToStack(StackItemSet &stack_items, 
                                        const std::list<VariableDeclaration *> &args, 
                                        int8_t position, 
                                        int8_t offset) {
                for (auto arg: args) {
                    StackItem stack_item(arg->GetName(),
                                         STACK_ITEM_ARGUMENT,
                                         position,
                                         arg->GetDelcaredType());
                    stack_items.insert(stack_item);
                    position += offset;
                }
            }

            size_t X86FuncEmitter::MapVarsToStack(StackItemSet &stack_items, const Statement* body, 
                                        int8_t position,
                                        int8_t offset, 
                                        int8_t depth_offset,
                                        int8_t align_by) {
                size_t depth = 0;
                if (STMT_COMPOUND == body->GetStatementType()) {
                    auto compound_statement = (CompoundStatement *) body;
                    auto statements = compound_statement->GetStatements();
                    for (Statement *statement: statements) {
                        if (STMT_DECLARATION == statement->GetStatementType()) {
                            auto declaration_statement = (DeclarationStatement *) statement;
                            auto declaration = declaration_statement->GetDeclaration();
                            if (DECLARATION_VARIABLE == declaration->GetDeclarationType()) {
                                auto variable = (VariableDeclaration *) declaration;
                                StackItem stack_item(variable->GetName(),
                                                     STACK_ITEM_VARIABLE,
                                                     position, variable->GetDelcaredType());
                                stack_items.insert(stack_item);
                                position += offset;
                                depth += depth_offset;
                            }
                        }
                    }

                    auto reminder = depth % (depth_offset * 2);
                    depth += reminder;
                }
                return depth;
            }

            size_t X86FuncEmitter::MapVarsToStack(StackItemSet &stack_items, const Statement* body) {
                const auto &config = this->GetConfig();
                if(EMITTER_WIN64 == config) {
                    return this->MapVarsToStack(stack_items, body, 
                        -8, -8, 8, 2);
                } else {
                    return 0;
                }
            }

            void X86FuncEmitter::SaveArgumentsWin64(const std::list<VariableDeclaration *> &arguments,
                                                    byte_vector &header) {
                auto iterator = arguments.begin();
                int8_t position = 16;

                for (size_t index = 0; index < WIN_X64_REG_COUNT; index++) {
                    if (iterator == arguments.end()) {
                        break;
                    }
                    auto arg = *(iterator);
                    if (IsDouble(arg)) {
                        auto reg = WIN_X64_ARG_DOUBLE_REGS[index];
                        auto ins_arg = this->_encoder.MOVSD(reg, X86_REG_RBP, position);
                        Utility::AppendTo(header, ins_arg);
                    } else {
                        auto reg = WIN_X64_ARG_INT_REGS[index];
                        auto ins_arg = this->_encoder.MOV(reg, X86_REG_RBP, position);
                        Utility::AppendTo(header, ins_arg);
                    }

                    iterator++;
                    position += 8;
                }
            }

            void X86FuncEmitter::SaveArgumentsLinux64(const std::list<VariableDeclaration *> &arguments,
                                                      byte_vector &header) {
                size_t param_index = 0;
                size_t float_index = 0;
                size_t other_index = 0;
                int8_t position = -8;                
                for(auto arg: arguments) {
                    if((param_index >= LINUX_X64_FLOAT_REG_COUNT) && (param_index >= LINUX_X64_REG_COUNT)) {
                        continue;
                    }

                    if(IsDouble(arg)) {
                        if(float_index >= LINUX_X64_FLOAT_REG_COUNT) {
                            continue;
                        }
                        auto reg = LINUX_X64_ARG_DOUBLE_REGS[float_index];
                        auto ins_arg = this->_encoder.MOVSD(reg, X86_REG_RBP, position);
                        Utility::AppendTo(header, ins_arg);
                        float_index ++;
                    } else {
                        if(float_index >= LINUX_X64_REG_COUNT) {
                            continue;
                        }
                        auto reg = LINUX_X64_ARG_INT_REGS[other_index];
                        auto ins_arg = this->_encoder.MOV(reg, X86_REG_RBP, position);
                        Utility::AppendTo(header, ins_arg);
                        other_index ++;
                    }

                    position -= 8;
                    param_index ++;
                }
            }

            bool X86FuncEmitter::IsDouble(VariableDeclaration *arg1) {
                auto type = arg1->GetDelcaredType();
                if (TYPE_SPEC_BASIC != type->GetType()) {
                    return false;
                }
                auto basic_data_type = (BasicDataTypeSpecification *) type;
                return !(BASIC_DATA_TYPE_DOUBLE != basic_data_type->GetDataType());
            }
        }
    }
}
