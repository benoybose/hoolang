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

#include "Node.hh"

#ifndef HCOPERATOR_H
#define HCOPERATOR_H

#include <memory>

namespace hooc {
    namespace ast {
        enum OperatorType {
            INVALID_OPERATOR,

            OPERATOR_ADD,
            OPERATOR_SUB,
            OPERATOR_DIV,
            OPERATOR_MUL,
            OPERATOR_MOD,

            OPERATOR_EQUAL,
            OPERATOR_NOT_EQUAL,
            OPERATOR_GREATER_THAN,
            OPERATOR_LESS_THAN,
            OPERATOR_GREATER_THAN_EQUAL,
            OPERATOR_LESS_THAN_EQUAL,
            OPERATOR_LOGICAL_AND,
            OPERATOR_LOGICAL_OR,

            OPERATOR_ASSIGN,
            OPERATOR_ASSIGN_INC,
            OPERATOR_ASSIGN_DEC,
            OPERATOR_ASSIGN_DIV,
            OPERATOR_ASSIGN_MUL,

            OPERATOR_BIT_OR,
            OPERATOR_BIT_AND,
            OPERATOR_BIT_XOR,
            OPERATOR_BIT_NOT,
            OPERATOR_BIT_SHIFT_RIGHT,
            OPERATOR_BIT_SHIFT_LEFT
        };

        class Operator {
        private:
            OperatorType _operatorType;
        public:
            explicit Operator(const std::string& operatorText);

        public:
            const OperatorType GetOperatorType() const;
        };
    }
};

#endif /* HCOPERATOR_H */

