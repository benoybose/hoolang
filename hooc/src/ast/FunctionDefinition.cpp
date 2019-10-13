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

#include "FunctionDefinition.hh"

namespace hooc {
    namespace ast {
        FunctionDefinition::FunctionDefinition(const std::string &declarator, std::string &name,
                                               TypeSpecification *returnType,
                                               std::list<VariableDeclaration *> &param_list,
                                               CompoundStatement *statement) :
                _declarator(declarator),
                _name(name),
                _returnType(returnType),
                _param_list(param_list),
                _statement(statement) {
        }

        FunctionDefinition::~FunctionDefinition() {
            delete this->_returnType;
            while(_param_list.begin() != _param_list.end()) {
                auto param = *(_param_list.begin());
                _param_list.remove(param);
                delete param;
            }
            delete this->_statement;
        }

        const std::string FunctionDefinition::GetName() const {
            return this->_name;
        }

        const TypeSpecification *FunctionDefinition::GetReturnType() const {
            return this->_returnType;
        }

        const std::list<VariableDeclaration *> &FunctionDefinition::GetParamList() const {
            return this->_param_list;
        }

        const void *FunctionDefinition::GetStatement() const {
            return this->_statement;
        }
    }
}
