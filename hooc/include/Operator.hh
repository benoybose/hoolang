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
 * File: hcoperator.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 27, March 2018
 */

#include "Node.hh"

#ifndef HCOPERATOR_H
#define HCOPERATOR_H

#include <memory>

namespace hooc {
    enum OperatorType {
        InvalidOperator,
        AddOperator,
        SubtractOperator,
        DivisionOperator,
        MultiplicationOperator,
        ModulationOperator
    };

    class Operator: public Node {
    private:
        OperatorType _operatorType;
    public:
        Operator();
        Operator(OperatorType operatorType);
        Operator(const Operator& opr);

    public:
        OperatorType getOperatorType();
    };

    namespace ast {
        typedef std::shared_ptr<hooc::Operator> Operator;
    }
};

#endif /* HCOPERATOR_H */

