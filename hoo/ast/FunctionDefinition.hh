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

#ifndef HC_FUNCTIONDEFINITION_HH
#define HC_FUNCTIONDEFINITION_HH

#include <hoo/ast/Definition.hh>
#include <hoo/ast/FunctionDeclaration.hh>
#include <hoo/ast/Statement.hh>

#include <string>
#include <list>
#include <memory>

namespace hoo
{
    namespace ast
    {
        class FunctionDefinition : public Definition
        {
        private:
            std::shared_ptr<FunctionDeclaration> _declaration;
            std::shared_ptr<Statement> _statements;

        public:
            FunctionDefinition(std::shared_ptr<FunctionDeclaration> declaration,
                               std::shared_ptr<Statement> statements);

            std::shared_ptr<FunctionDeclaration> GetDeclaration();

            std::shared_ptr<Statement> GetBody();

        public:
            virtual ~FunctionDefinition();
        };
    } // namespace ast
} // namespace hoo

#endif //PROJECT_FUNCTIONDEFINITION_HH
