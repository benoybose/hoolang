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

#include <cstdlib>

#include "BinaryExpression.hh"
#include "ast/Expression.hh"
#include "Operator.hh"

namespace hooc {
    namespace ast {
        BinaryExpression::BinaryExpression(Expression *lvalue,
                Operator *opr,
                Expression *rvalue):
                Expression(EXPRESSION_BINARY),
                _lvalue(lvalue), _operator(opr),
                _rvalue(rvalue) {
        }

        BinaryExpression::~BinaryExpression() {
            delete this->_lvalue;
            delete this->_rvalue;
            delete this->_rvalue;
        }

        const Expression *BinaryExpression::GetLeftExpression() const {
            return this->_lvalue;
        }

        const Operator *BinaryExpression::GetOperator() const {
            return this->_operator;
        }

        const Expression *BinaryExpression::GetRightExpression() const {
            return this->_rvalue;
        }
    }
}