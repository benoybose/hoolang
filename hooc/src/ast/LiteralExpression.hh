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

#ifndef _LITERALTYPEEXPR_H_
#define _LITERALTYPEEXPR_H_

#include "Expression.hh"
#include "HooTypes.hh"
#include "Value.hh"

#include <cstdint>
#include <cstdbool>
#include <string>

namespace hooc {
    namespace ast {
        enum LiteralType {
            LITERAL_INTEGER,
            LITERAL_CHARACTER,
            LITERAL_STRING,
            LITERAL_BOOLEAN,
            LITERAL_DOUBLE,
            LITERAL_BYTE
        };

        class LiteralExpression : public Expression {
        private:
            LiteralType _literalType;
            std::string _value;

        public:
            LiteralExpression(LiteralType literaltype, std::string& value);
            LiteralExpression(LiteralType literaltype, const std::string& value);

        public:
            const LiteralType GetLiteralType() const;
            const std::string GetValue() const;
        };
    }
};

#endif
