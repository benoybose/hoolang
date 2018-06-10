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
 * File: hcliteralexpr.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#ifndef _LITERALTYPEEXPR_H_
#define _LITERALTYPEEXPR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "hcnode.hh"
#include "hcexpr.hh"

namespace hooc {
    enum LiteralType {
        HC_LITERAL_SBYTE,
        HC_LITERAL_BYTE,
        HC_LITERAL_INT32,
        HC_LITERAL_INT64,
        HC_LITERAL_FLOAT,
        HC_LITERAL_DOUBLE,
        HC_LITERAL_CHAR,
        HC_LITERAL_STRING,
        HC_LITERAL_BOOL
    };

    union LiteralValue {
        int32_t intval;
        int64_t longval;
        uint8_t byteval;
        char charval;
        char* stringval;
        bool boolval;
    };

    class LiteralExpression: Expression {
    private:
        LiteralType _literalType;
        LiteralValue _value;
        size_t _size;

    public:
        LiteralExpression(LiteralType literaltype, LiteralValue value, size_t size);

    public:
        LiteralType getLiteralType();
        LiteralValue getValue();
        size_t getSize();
    };
};

#endif
