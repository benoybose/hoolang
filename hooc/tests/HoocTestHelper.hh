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

#ifndef HOOLANG_HOOCTESTHELPER_HH
#define HOOLANG_HOOCTESTHELPER_HH

#include <boost/test/unit_test.hpp>
#include "ast/LiteralExpression.hh"

#define BOOST_CHECK_LITERAL_EXPRESSION(expr, type, value)\
    BOOST_CHECK_EQUAL(EXPRESSION_LITERAL, expr->GetExpressionType());\
    BOOST_CHECK_EQUAL(type, ((LiteralExpression*) expr)->GetLiteralType());\
    BOOST_CHECK_EQUAL(value, ((LiteralExpression*) expr)->GetValue())

#define BOOST_CHECK_REFERENCE_EXPRESSION(expr, value)\
    BOOST_CHECK_EQUAL(EXPRESSION_REFERENCE, expr->GetExpressionType());\
    BOOST_CHECK_EQUAL(value, ((ReferenceExpression*) expr)->GetName());\
    BOOST_CHECK_EQUAL(nullptr, ((ReferenceExpression*) expr)->GetParent())

#endif //HOOLANG_HOOCTESTHELPER_HH
