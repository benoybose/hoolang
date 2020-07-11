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

#include <utility>

#include <hoo/ast/FunctionDeclaration.hh>

namespace hoo {
    namespace ast {

        FunctionDeclaration::FunctionDeclaration(DeclaratorType declarator_type, TypeSpecification *return_type,
                                                 std::string name,
                                                 std::list<VariableDeclaration *> param_list) :
                Declaration(DECLARATION_FUNCTION, declarator_type),
                _return_type(return_type),
                _name(std::move(name)),
                _param_list(std::move(param_list)) {
        }

        TypeSpecification *FunctionDeclaration::GetReturnType() const {
            return _return_type;
        }

        const std::string &FunctionDeclaration::GetName() const {
            return _name;
        }

        const std::list<VariableDeclaration *> &FunctionDeclaration::GetParamList() const {
            return _param_list;
        }

        FunctionDeclaration::~FunctionDeclaration() {
                delete this->_return_type;
        }
    }
}
