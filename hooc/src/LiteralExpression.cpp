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
 * File: literaltype.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#include <LiteralExpression.hh>

namespace hooc
{
    LiteralExpression::LiteralExpression() : Expression(ExpressionType::LiteralExpr) {
        this->_literalType = LiteralType ::InvalidLiteral;
    }

    LiteralExpression::LiteralExpression(hooc::LiteralType literalType, const char* text):
            Expression(ExpressionType::LiteralExpr) {
        this->_literalType = literalType;

        switch(literalType) {
            case LiteralType ::Integer: this->_integerValue = atol(text); break;
            case LiteralType ::Long: this->_longValue = atoll(text); break;
            case LiteralType ::Character: this->_characterValue = text[0]; break;
            case LiteralType ::String: this->_stringValue = std::string(text); break;
            case LiteralType ::Boolean:
                if (std::string(text) == "true")
                    this->_booleanValue = true;
                else if(std::string(text) == "false")
                    this->_booleanValue = false;
                break;
            case LiteralType ::Double: this->_doubleValue = std::stold(text); break;
        }
    }

    LiteralExpression::LiteralExpression(const hooc::LiteralExpression &literalExpression):
            Expression(ExpressionType::LiteralExpr) {
        this->_literalType = literalExpression._literalType;
        this->_integerValue = literalExpression._integerValue;
        this->_longValue = literalExpression._longValue;
        this->_characterValue = literalExpression._characterValue;
        this->_stringValue = literalExpression._stringValue;
        this->_booleanValue = literalExpression._booleanValue;
        this->_doubleValue = literalExpression._doubleValue;
    }

    LiteralType LiteralExpression::GetListeralType() {
        return this->_literalType;
    }
}