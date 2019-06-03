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

#ifndef REFERENCEEXPRESSION_HH
#define REFERENCEEXPRESSION_HH

#include "Expression.hh"

#include <string>

namespace hooc {
    namespace ast {
        class ReferenceExpression: public Expression {
        private:
            ReferenceExpression* _parent;
            std::string _name;

        public:
            explicit ReferenceExpression(std::string& name);
            explicit ReferenceExpression(const std::string& name);
            ReferenceExpression(ReferenceExpression* parent, std::string& name);
            ReferenceExpression(ReferenceExpression* parent, const std::string& name);

        public:
            const std::string& GetName() const;
            const ReferenceExpression* GetParent() const;
        };
    }
}




#endif //PROJECT_REFERENCEEXPRESSION_HH