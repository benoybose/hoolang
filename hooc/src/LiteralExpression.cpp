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
    LiteralExpression::LiteralExpression(hooc::LiteralType literalType, const char* text):
            Expression(EXPRESSION_LITERAL) {
        this->_literalType = literalType;

        switch(literalType) {
            case LiteralType ::LITERAL_INTEGER: this->_longValue = std::stoll(text); break;
            case LiteralType ::LITERAL_CHARACTER: this->_characterValue = text[0]; break;
            case LiteralType ::LITERAL_STRING: this->_stringValue = std::string(text); break;
            case LiteralType ::LITERAL_BOOLEAN:
                if (std::string(text) == "true")
                    this->_booleanValue = true;
                else if(std::string(text) == "false")
                    this->_booleanValue = false;
                break;
            case LiteralType ::LITERAL_DOUBLE: this->_doubleValue = std::stold(text); break;
        }
    }

    LiteralType LiteralExpression::GetListeralType() {
        return this->_literalType;
    }
}