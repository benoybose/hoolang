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

#ifndef ARRAY_ACCESSEXPRESSION_HH
#define ARRAY_ACCESSEXPRESSION_HH

#include <hoo/ast/Expression.hh>
#include <memory>

namespace hoo
{
    namespace ast
    {
        class ArrayAccessExpression : public Expression
        {
        private:
            std::shared_ptr<Expression> _container;
            std::shared_ptr<Expression> _index;

        public:
            ArrayAccessExpression(std::shared_ptr<Expression> container,
                                  std::shared_ptr<Expression> index);

        public:
            std::shared_ptr<Expression> GetContainer();
            std::shared_ptr<Expression> GetIndex();

        public:
            ~ArrayAccessExpression() override;
        };
    } // namespace ast
} // namespace hoo

#endif //PROJECT_ARRAYACCESSEXPRESSION_HH
