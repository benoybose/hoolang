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

#include <hoo/emitter/ExpressionEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/CastEmitter.hh>
#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/emitter/BinaryExpressionEmitter.hh>

namespace hoo
{
    namespace emitter
    {
        ExpressionEmitter::ExpressionEmitter(const std::shared_ptr<Expression> expression,
                                             const EmitterContext &emitter_context)
            : EmitterBase(emitter_context),
              _expression(expression)
        {
        }

        Value *ExpressionEmitter::Emit()
        {
            auto value = Emit(_expression);
            return value;
        }

        Value *ExpressionEmitter::Emit(const std::shared_ptr<Expression> &expression)
        {
            auto expr_type = expression->GetExpressionType();
            switch (expr_type)
            {
            case EXPRESSION_LITERAL:
            {
                auto const &literal_expression = dynamic_pointer_cast<LiteralExpression>(expression);
                return EmitLiteral(literal_expression);
            }

            case EXPRESSION_BINARY:
            {
                auto const &binary_expression = dynamic_pointer_cast<BinaryExpression>(expression);
                return EmitBinary(binary_expression);
            }

            case EXPRESSION_REFERENCE:
            {
                auto const &ref_expression = dynamic_pointer_cast<ReferenceExpression>(expression);
                return EmitReference(ref_expression);
            }

            case EXPRESSION_ARRAY:
            {
                auto const array_expression = dynamic_pointer_cast<ArrayAccessExpression>(expression);
                return EmitArrayAccessExpression(array_expression);
            }

            case EXPRESSION_CAST:
            {
                auto const &cast_expression = dynamic_pointer_cast<CastExpression>(expression);
                return EmitCast(cast_expression);
            }

            case EXPRESSION_INVOKE:
            {
                auto const &invoke_expression = dynamic_pointer_cast<InvokeExpression>(expression);
                return EmitInvoke(invoke_expression);
            }
            }
            return nullptr;
        }

        Value *ExpressionEmitter::EmitLiteral(const std::shared_ptr<LiteralExpression> &expression)
        {
            throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
        }

        Value *ExpressionEmitter::EmitBinary(const std::shared_ptr<BinaryExpression> &expression)
        {
            BinaryExpressionEmitter emitter(expression, _emitter_context);
            auto value = emitter.Emit();
            return value;
        }

        Value *ExpressionEmitter::EmitReference(const std::shared_ptr<ReferenceExpression> &expression)
        {
            std::string name = expression->GetName();
            auto block_context = _emitter_context.GetCurrentBlockContext();
            auto symbol = block_context->Lookup(name);
            return symbol;
        }

        Value *ExpressionEmitter::EmitArrayAccessExpression(const std::shared_ptr<ArrayAccessExpression> &expression)
        {
            throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
        }

        Value *ExpressionEmitter::EmitCast(const std::shared_ptr<CastExpression> &expression)
        {
            CastEmitter emitter(expression, _emitter_context);
            return emitter.Emit();
        }

        Value *ExpressionEmitter::EmitInvoke(const std::shared_ptr<InvokeExpression> &expression)
        {
            throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
        }
    }
}