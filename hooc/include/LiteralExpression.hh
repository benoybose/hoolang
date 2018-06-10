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

#include "Expression.hh"

#include <cstdint>
#include <cstdbool>
#include <string>


namespace hooc {
    enum LiteralType {
        InvalidLiteral,
        Integer,
        Long,
        Character,
        String,
        Boolean,
        Double
    };

    class LiteralExpression: Expression {
    private:
        LiteralType _literalType = LiteralType::InvalidLiteral;
        int32_t _integerValue = 0;
        int64_t _longValue = 0;
        char _characterValue;
        std::string _stringValue;
        bool _booleanValue;
        long double _doubleValue;


    public:
        LiteralExpression();
        LiteralExpression(LiteralType literaltype, const char* value);
        LiteralExpression(const LiteralExpression& literalExpression);

    public:
        LiteralType GetListeralType();
        inline int32_t GetInteger() { return _integerValue; }
        inline int64_t GetLong() { return _longValue; };
        inline char GetCharacter() { return _characterValue; }
        inline std::string GetString() { return _stringValue; }
        inline bool GetBoolean() { return _booleanValue; }
        inline long double GetDouble() { return _doubleValue; }
    };
};

#endif
