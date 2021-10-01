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
#include <hoo/ast/Expression.hh>
#include <hoo/ast/CastExpression.hh>
#include <hoo/ast/LiteralExpression.hh>
#include <hoo/ast/BinaryExpression.hh>
#include <hoo/ast/ReferenceExpression.hh>
#include <hoo/ast/ArrayAccessExpression.hh>
#include <hoo/ast/InvokeExpression.hh>
#include <llvm/IR/Value.h>

#include <memory>

using namespace hoo::ast;

namespace hoo
{
    namespace emitter
    {
        class ExpressionEmitter : public EmitterBase
        {
            private:
            std::shared_ptr<Expression> _expression;

            public:
            ExpressionEmitter(const std::shared_ptr<Expression> expression,
            const EmitterContext& emitter_context);

            public:
            Value *Emit();

            private:
            Value* Emit(const std::shared_ptr<Expression> &expression);
            Value* EmitLiteral(const std::shared_ptr<LiteralExpression> &expression);
            Value* EmitBinary(const std::shared_ptr<BinaryExpression> &expression);
            Value* EmitReference(const std::shared_ptr<ReferenceExpression> &expression);
            Value* EmitArrayAccessExpression(const std::shared_ptr<ArrayAccessExpression> &expression);
            Value* EmitCast(const std::shared_ptr<CastExpression> &expression);
            Value* EmitInvoke(const std::shared_ptr<InvokeExpression> &expression);
            Value* EmitOperation(const OperatorType operator_type, Value* left_value, Value* right_value,
            const std::shared_ptr<BinaryExpression> &expression);
            Value* EmitSub(Value* left_value, Value* right_value,
            const std::shared_ptr<BinaryExpression> &expression);
            Value* EmitSubFromInt(Value* left_value, Value* right_value,
            const std::shared_ptr<BinaryExpression> &expression, BasicDataTypeType right_basic_type);
            Value* EmitSubFromDouble(Value* left_value, Value* right_value,
            const std::shared_ptr<BinaryExpression> &expression, BasicDataTypeType right_basic_type);
            Value* EmitAdd(Value* left_value, Value* right_value);
            
        };
    }
}