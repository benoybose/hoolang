/*
 * Copyright 2021 Benoy Bose
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

#include <hoo/emitter/EmitterBase.hh>
#include <hoo/ast/BinaryExpression.hh>
#include <hoo/ast/Expression.hh>
#include <hoo/ast/Operator.hh>
#include <hoo/ast/BasicDataTypes.hh>
#include <llvm/IR/Value.h>

#include <memory>

using namespace hoo::ast;
using namespace llvm;

namespace hoo
{
    namespace emitter
    {
        class BinaryExpressionEmitter : public EmitterBase
        {
            private:
            std::shared_ptr<BinaryExpression> _binary_expression;
            std::shared_ptr<Expression> _left_expression;
            std::shared_ptr<Expression> _right_expression;
            std::shared_ptr<hoo::ast::Operator> _operator;
            Value* _left_value;
            Value* _right_value;
            Type* _left_type;
            Type* _right_type;
            BasicDataTypeType _left_basic_type;
            BasicDataTypeType _right_basic_type;

            public:
            BinaryExpressionEmitter (std::shared_ptr<BinaryExpression> binary_expression,
            const EmitterContext &emitter_context);

            public:
            bool IsBothBasicDataType();
            Value *Emit();

            private:
            Value *EmitOperation(const OperatorType operator_type);
            Value *EmitAdd();
            Value *EmitSub();

            Value *EmitSubFromDouble();
            Value *EmitSubFromInt();
            Value *EmitSubFromByte();
        };
    }
}