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

#ifndef HCBINARYEXP_H
#define HCBINARYEXP_H

#include <hoo/ast/Expression.hh>
#include <hoo/ast/Operator.hh>

#include <memory>

namespace hoo
{
    namespace ast
    {
        class BinaryExpression : public Expression
        {
        private:
            std::shared_ptr<Expression> _lvalue;
            std::shared_ptr<Operator> _operator;
            std::shared_ptr<Expression> _rvalue;

        public:
            BinaryExpression(std::shared_ptr<Expression> lvalue,
                             std::shared_ptr<Operator> opr,
                             std::shared_ptr<Expression> rvalue);

        public:
            std::shared_ptr<Expression> GetLeftExpression();
            std::shared_ptr<Operator> GetOperator();
            std::shared_ptr<Expression> GetRightExpression();

        public:
            virtual ~BinaryExpression();
        };
    } // namespace ast
} // namespace hoo

#endif /* HCBINARYEXPR_H */
