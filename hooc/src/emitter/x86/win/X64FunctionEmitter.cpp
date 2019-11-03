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

using namespace hooc::ast;

namespace hooc {
    namespace emitter {
        namespace x86 {
            namespace win {
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
                    for(auto stack_item: stack_items) {
                        context->AddItem(stack_item);
                    }
                    return context;
                }
            }
        }
    }
}
