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

#include "VariableDeclaration.hh"

namespace hooc {
    namespace ast {
        VariableDeclaration::VariableDeclaration(DeclaratorType declarator,
                                                 const std::string &name,
                                                 TypeSpecification *declared_type,
                                                 Expression *initializer) :
                Declaration(DECLARATION_VARIABLE, declarator),
                _declarator(declarator),
                _name(name),
                _declared_type(declared_type),
                _initializer(initializer) {
        }

        VariableDeclaration::~VariableDeclaration() {
            delete this->_declared_type;
            delete this->_initializer;
        }

        const TypeSpecification *VariableDeclaration::GetDelcaredType() const {
            return _declared_type;
        }

        const std::string &VariableDeclaration::GetName() const {
            return _name;
        }

        const Expression *VariableDeclaration::GetInitializer() const {
            return _initializer;
        }
    }
}
