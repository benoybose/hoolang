/*
 * Copyright 2020 Benoy Bose
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

#ifndef PROJECT_DECLARATION_HH
#define PROJECT_DECLARATION_HH

#include <hoo/ast/Declaration.hh>
#include <hoo/ast/Declarator.hh>
#include <hoo/ast/TypeSpecification.hh>
#include <hoo/ast/Expression.hh>

#include <string>

namespace hoo {
    namespace ast {
        class VariableDeclaration: public Declaration {
        private:
            DeclaratorType _declarator;
            TypeSpecification *_declared_type;
            std::string _name;
            Expression *_initializer;

        public:
            VariableDeclaration(DeclaratorType declarator,
                                const std::string &name,
                                TypeSpecification *declared_type,
                                Expression *initializer
            );

        public:
            const TypeSpecification *GetDelcaredType() const;
            const std::string &GetName() const;
            const Expression *GetInitializer() const;

        public:
            virtual ~VariableDeclaration();
        };
    }
}


#endif //PROJECT_DECLARATION_HH
