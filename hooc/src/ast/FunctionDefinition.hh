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

#ifndef PROJECT_FUNCTIONDEFINITION_HH
#define PROJECT_FUNCTIONDEFINITION_HH

#include "TypeSpecification.hh"
#include "Declaration.hh"

#include <string>
#include <list>

namespace hooc {
    namespace ast {
        class FunctionDefinition {
        private:
            TypeSpecification *_returnType;
            std::string _name;
            std::list<Declaration *> _param_list;
            void *_statement;
        public:
            FunctionDefinition(std::string name,
                               TypeSpecification *returnType,
                               std::list<Declaration *> &param_list,
                               void *statement);

        public:
            const std::string GetName() const;

            const TypeSpecification *GetReturnType() const;

            const std::list<Declaration *> &GetParamList() const;

            const void *GetStatement() const;
        };
    }
}

#endif //PROJECT_FUNCTIONDEFINITION_HH
