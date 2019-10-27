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


#include <emitter/x86/X86Definitions.hh>
#include <emitter/x86/WindowsX64Emitter.hh>
#include <misc/Utility.hh>
#include <ast/BasicDataTypes.hh>
#include <ast/Definition.hh>
#include <ast/FunctionDefinition.hh>
#include <ast/CompoundStatement.hh>

using namespace std;
using namespace hooc::misc;

namespace hooc {
    namespace emitter {
        namespace x86 {

            const X86RegisterType WIN_X86_ARG_REGISTERS[4] = {
                    X86_REG_RCX,
                    X86_REG_RDX,
                    X86_REG_R8,
                    X86_REG_R9
            };

            WindowsX64Emitter::WindowsX64Emitter(const Unit *unit) :
                    Emitter(unit) {
            }

            std::list<Code *> WindowsX64Emitter::GenerateCode() {
                std::list<Code *> codes;
                auto unit_items = this->GetUnit()
                        ->GetItems();
                for (auto unit_item: unit_items) {
                    try {
                        if (unit_item->GetUnitItemType() == UNIT_ITEM_DEFINITION) {
                            auto definition = (Definition *) unit_item;
                            if (DEFINITION_FUNCTION == definition->GetDefinitionType()) {
                                auto function_definition = (FunctionDefinition *) definition;
                                auto code = this->GenerateCode(function_definition);
                                if (nullptr != code) {
                                    codes.push_back(code);
                                }
                            }
                        }
                    } catch (const std::exception &ex) {
                        // todo: Handle exception
                    }
                }
                return codes;
            }

            Code *WindowsX64Emitter::GenerateCode(FunctionDefinition *function_definition) {
                byte_vector header;
                byte_vector body;
                byte_vector footer;

                auto ins_return = this->_encoder.RET(false);
                Utility::AppendTo(footer, ins_return);

                auto declaration = function_definition->GetDeclaration();
                const auto& arguments = declaration->GetParamList();
                if(!arguments.empty()) {
                    GenerateCode(arguments, header, footer);
                }

                auto statement = function_definition->GetBody();
                if(STMT_COMPOUND == statement->GetStatementType()) {
                    auto compound_statement = (CompoundStatement*) statement;
                    if(compound_statement->GetStatements().empty()) {
                        auto ins_nop = this->_encoder.NOP();
                        Utility::AppendTo(body, ins_nop);
                    }
                }
                return nullptr;
            }

            void WindowsX64Emitter::GenerateCode(std::list<VariableDeclaration *> arguments,
                                                 byte_vector &header,
                                                 byte_vector &footer) {
                auto push_rbp = this->_encoder.PUSH(X86_REG_RBP);
                Utility::AppendTo(header, push_rbp);
                auto mov_rsp_rbp = this->_encoder.MOV(X86_REG_RSP, X86_REG_RBP);
                Utility::AppendTo(header, mov_rsp_rbp);

                auto iterator = arguments.begin();
                uint8_t offset = 0x10;

                for (auto reg : WIN_X86_ARG_REGISTERS) {
                    if (iterator == arguments.end()) {
                        break;
                    }
                    auto arg = *(iterator);
                    if (IsDouble(arg)) {
                        // todo: Process double argument
                    } else {
                        auto ins_arg = this->_encoder.MOV(reg,
                                                          X86_REG_RBP,
                                                          offset);
                    }

                    iterator ++;
                    offset += 0x08;
                }
            }

            bool WindowsX64Emitter::IsDouble(VariableDeclaration *arg1) {
                return ((TYPE_SPEC_BASIC == arg1->GetDelcaredType()->GetType())
                        && (NAME_DOUBLE == arg1->GetName()));
            }
        }
    }
}

