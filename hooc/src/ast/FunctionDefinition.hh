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

#ifndef HC_FUNCTIONDEFINITION_HH
#define HC_FUNCTIONDEFINITION_HH

#include "Definition.hh"
#include "FunctionDeclaration.hh"
#include "CompoundStatement.hh"

#include <string>
#include <list>

namespace hooc {
    namespace ast {
        class FunctionDefinition: public Definition {
        private:
            FunctionDeclaration *_declaration;
            CompoundStatement *_statements;

        public:
            FunctionDefinition(FunctionDeclaration *declaration,
                               CompoundStatement *statements);

            FunctionDeclaration *GetDeclaration() const;

            CompoundStatement *GetStatements() const;

        public:
            virtual ~FunctionDefinition();
        };
    }
}

#endif //PROJECT_FUNCTIONDEFINITION_HH
