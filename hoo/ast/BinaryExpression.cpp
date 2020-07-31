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

#include <cstdlib>

#include <hoo/ast/BinaryExpression.hh>
#include <hoo/ast/Expression.hh>
#include <hoo/ast/Operator.hh>

namespace hoo
{
    namespace ast
    {
        BinaryExpression::BinaryExpression(std::shared_ptr<Expression> lvalue,
                                           std::shared_ptr<Operator> opr,
                                           std::shared_ptr<Expression> rvalue,
                                           std::shared_ptr<TypeSpecification> type)
            : Expression(EXPRESSION_BINARY, type),
              _lvalue(lvalue),
              _operator(opr),
              _rvalue(rvalue)
        {
        }

        std::shared_ptr<Expression> BinaryExpression::GetLeftExpression()
        {
            return this->_lvalue;
        }

        std::shared_ptr<Operator> BinaryExpression::GetOperator()
        {
            return this->_operator;
        }

        std::shared_ptr<Expression> BinaryExpression::GetRightExpression()
        {
            return this->_rvalue;
        }

        BinaryExpression::~BinaryExpression()
        {
        }
    } // namespace ast
} // namespace hoo