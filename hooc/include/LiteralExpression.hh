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
#include "HooTypes.hh"

#include <cstdint>
#include <cstdbool>
#include <string>


namespace hooc {
    enum LiteralType {
        LITERAL_INVALID,
        LITERAL_INTEGER,
        LITERAL_CHARACTER,
        LITERAL_STRING,
        LITERAL_BOOLEAN,
        LITERAL_DOUBLE
    };

    typedef ::hoo::Integer Integer;
    typedef ::hoo::Character Character;
    typedef ::hoo::String String;
    typedef ::hoo::Boolean Boolean;
    typedef ::hoo::Double Double;

    class LiteralExpression: public Expression {
    private:
        LiteralType _literalType = LITERAL_INVALID;
        Integer _longValue = 0;
        Character _characterValue;
        String _stringValue;
        Boolean _booleanValue;
        Double _doubleValue;

    public:
        LiteralExpression(LiteralType literaltype, const char* value);

    public:
        LiteralType GetListeralType();
        inline Integer GetInteger() const { return _longValue; }
        inline Character GetCharacter() const { return _characterValue; }
        inline String GetString() const { return _stringValue; }
        inline Boolean GetBoolean() const { return _booleanValue; }
        inline Double GetDouble() const { return _doubleValue; }
    };
};

#endif
