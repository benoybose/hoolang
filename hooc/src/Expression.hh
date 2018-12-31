/*
 * Copyright 2018 Benoy Bose
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

/**
 * File: hcexpr.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 29, March 2018
 */

#ifndef HCEXPR_H
#define HCEXPR_H

#include "Node.hh"
#include <memory>
#include <string>

namespace hooc {
    enum ExpressionType {
        EXPRESSION_INVALID,
        EXPRESSION_LITERAL,
        EXPRESSION_BINARY
    };

    class Expression: public Node {

    private:
        ExpressionType _expressionType;

    public:
        explicit Expression(ExpressionType expressionType);

    public:
        ExpressionType GetExpressionType();
    };

    namespace ast {
        typedef std::shared_ptr<hooc::Expression> Expression;
    }
}

#endif /* HCEXPR_H */

