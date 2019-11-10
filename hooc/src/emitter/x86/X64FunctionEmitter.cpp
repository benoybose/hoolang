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

#include "X64FunctionEmitter.hh"
#include <emitter/FunctionEmitterContext.hh>
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
            const X86RegisterType WIN_X86_ARG_DOUBLE_REGS[WIN_X64_REG_COUNT] = {
                    X86_REG_XMM0,
                    X86_REG_XMM1,
                    X86_REG_XMM2,
                    X86_REG_XMM3
            };
            const X86RegisterType WIN_X86_ARG_INT_REGS[WIN_X64_REG_COUNT] = {
                    X86_REG_RCX,
                    X86_REG_RDX,
                    X86_REG_R8,
                    X86_REG_R9
            };

            X64FunctionEmitter::X64FunctionEmitter(FunctionDefinition *definition)
                    : FunctionEmitter(definition) {
            }

            FunctionEmitterContext *X64FunctionEmitter::CreateFunctionEmitterContext() {
                FunctionEmitterContext* context = nullptr;
                NameMangler mangler;

                auto function_declaration = this->GetDefinition()
                        ->GetDeclaration();
                auto args = function_declaration->GetParamList();
                StackItemSet stack_items;
                std::int64_t position = 0x10;
                for(auto arg: args) {
                    StackItem stack_item(arg->GetName(),
                                         position,
                                         arg->GetDelcaredType());
                    stack_items.insert(stack_item);
                    position += 0x08;
                }

                auto body = this->GetDefinition()
                        ->GetBody();

                position = -8;
                size_t depth = 0;
                if(STMT_COMPOUND == body->GetStatementType()) {
                    auto compound_statement = (CompoundStatement*) body;
                    auto statements = compound_statement->GetStatements();
                    for(Statement* statement: statements) {
                        if(STMT_DECLARATION == statement->GetStatementType()) {
                            auto declaration_statement = (DeclarationStatement*) statement;
                            auto declaration =  declaration_statement->GetDeclaration();
                            if(DECLARATION_VARIABLE == declaration->GetDeclarationType()) {
                                auto variable = (VariableDeclaration*) declaration;
                                StackItem stack_item(variable->GetName(),
                                                     position, variable->GetDelcaredType());
                                stack_items.insert(stack_item);
                                position -= 8;
                                depth +=8;
                            }
                        }
                    }
                }

                if(8 == depth % 16) {
                    depth += 8;
                }

                auto name = mangler.Mangle(function_declaration);
                context = new FunctionEmitterContext(depth, name);
                for(const auto& stack_item: stack_items) {
                    context->AddItem(stack_item);
                }
                return context;
            }

            Code *X64FunctionEmitter::GenerateCode() {
                byte_vector header;
                byte_vector body;
                byte_vector footer;

                auto function_definition = this->GetDefinition();
                auto declaration = function_definition->GetDeclaration();
                const auto &arguments = declaration->GetParamList();
                if (!arguments.empty()) {
                    ProcessArguments(arguments, header, footer);
                }

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

            void X64FunctionEmitter::ProcessArguments(const std::list<VariableDeclaration *> &arguments,
                                                      byte_vector &header, byte_vector &footer) {
                auto push_rbp = this->_encoder.PUSH(X86_REG_RBP);
                Utility::AppendTo(header, push_rbp);
                auto mov_rsp_rbp = this->_encoder.MOV(X86_REG_RSP, X86_REG_RBP);
                Utility::AppendTo(header, mov_rsp_rbp);

                auto iterator = arguments.begin();
                uint8_t offset = 0x10;

                for (size_t index = 0; index < WIN_X64_REG_COUNT; index++) {
                    if (iterator == arguments.end()) {
                        break;
                    }
                    auto arg = *(iterator);
                    if (IsDouble(arg)) {
                        auto reg = WIN_X86_ARG_DOUBLE_REGS[index];
                        auto ins_arg = this->_encoder.MOVSD(reg,
                                                            X86_REG_RBP,
                                                            offset);
                        Utility::AppendTo(header, ins_arg);
                    } else {
                        auto reg = WIN_X86_ARG_INT_REGS[index];
                        auto ins_arg = this->_encoder.MOV(reg,
                                                          X86_REG_RBP,
                                                          offset);
                        Utility::AppendTo(header, ins_arg);
                    }

                    iterator++;
                    offset += 0x08;
                }

                auto pop_rbp = this->_encoder.POP(X86_REG_RBP);
                Utility::AppendTo(footer, pop_rbp);
            }

            bool X64FunctionEmitter::IsDouble(VariableDeclaration *arg1) {
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
