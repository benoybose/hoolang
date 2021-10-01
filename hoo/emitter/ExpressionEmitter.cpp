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
            auto const &left_expr = expression->GetLeftExpression();
            auto const &right_expr = expression->GetRightExpression();
            auto const &opr = expression->GetOperator();

            auto left_value = Emit(left_expr);
            if (!left_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_LEFT_EXPRESSION,
                                       ERR_POS(left_expr));
            }

            auto right_value = Emit(right_expr);
            if (!right_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_RIGHT_EXPRESSION,
                                       ERR_POS(right_expr));
            }

            auto const operator_type = opr->GetOperatorType();
            auto value = EmitOperation(operator_type,
                                       left_value, right_value, expression);
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

        Value *ExpressionEmitter::EmitOperation(const OperatorType operator_type,
                                                Value *left_value,
                                                Value *right_value,
                                                const std::shared_ptr<BinaryExpression> &expression)
        {
            switch (operator_type)
            {
            case OPERATOR_ADD:
                return EmitAdd(left_value, right_value);
            case OPERATOR_SUB:
                return EmitSub(left_value, right_value, expression);
            default:
                throw EmitterException(ERR_EMITTER_BINARY_FAILED_EXPRESSION,
                                       ERR_POS(expression));
            }
        }

        Value *ExpressionEmitter::EmitSub(Value *left_value, Value *right_value,
                                          const std::shared_ptr<BinaryExpression> &expression)
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();

            auto left_basic_type = EmitterUtils::GetBasicDataType(left_value);
            auto right_basic_type = EmitterUtils::GetBasicDataType(right_value);

            if ((left_basic_type == BASIC_DATA_TYPE_INVALID) ||
                (right_basic_type == BASIC_DATA_TYPE_INVALID))
            {
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING,
                                       ERR_POS(expression));
            }
            else
            {
                switch (left_basic_type)
                {
                case BASIC_DATA_TYPE_INT:
                    return EmitSubFromInt(left_value, right_value, expression, right_basic_type);
                case BASIC_DATA_TYPE_DOUBLE:
                    return EmitSubFromDouble(left_value, right_value, expression, right_basic_type);
                default:
                    throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(expression));
                }
            }

            throw EmitterException(ERR_EMITTER_SUB_OPERATION_UNSUPPORTED, ERR_POS(expression));
        }

        Value *ExpressionEmitter::EmitSubFromInt(Value *left_value, Value *right_value,
                                                 const std::shared_ptr<BinaryExpression> &expression,
                                                 BasicDataTypeType right_basic_type)
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            switch (right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                right_value = builder->CreateZExt(right_value, Type::getInt64Ty(*context));
                auto value = builder->CreateNSWSub(left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                left_value = builder->CreateSIToFP(left_value, Type::getDoubleTy(*context));
                auto value = builder->CreateFSub(left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto value = builder->CreateNSWSub(left_value, right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(expression));
            }
        }

        Value *ExpressionEmitter::EmitSubFromDouble(Value *left_value, Value *right_value,
                                 const std::shared_ptr<BinaryExpression> &expression, BasicDataTypeType right_basic_type)
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            auto double_type = Type::getDoubleTy(*context);

            switch (right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                right_value = builder->CreateZExt(right_value, Type::getInt64Ty(*context));
                right_value = builder->CreateSIToFP(right_value, double_type);
                auto value = builder->CreateFSub(left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto value = builder->CreateFSub(left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                right_value = builder->CreateSIToFP(right_value, double_type);
                auto value = builder->CreateFSub(left_value, right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(expression));
            }
        }

        Value *ExpressionEmitter::EmitAdd(Value *left_value,
                                          Value *right_value)
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();

            auto const left_type = left_value->getType();
            auto const right_type = right_value->getType();
            if ((left_type->isIntegerTy()) && (right_type->isIntegerTy()))
            {
                auto left_bits = left_type->getIntegerBitWidth();
                auto right_bits = right_type->getIntegerBitWidth();
                if (left_bits < right_bits)
                {
                    left_value = builder->CreateCast(Instruction::CastOps::ZExt,
                                                     left_value, right_type);
                }
                else if (left_bits > right_bits)
                {
                    right_value = builder->CreateCast(Instruction::CastOps::ZExt,
                                                      right_value, left_type);
                }

                auto value = builder->CreateNSWAdd(left_value, right_value);
                return value;
            }
            else if ((left_type->isIntegerTy()) && (right_type->isDoubleTy()))
            {
                left_value = builder->CreateSIToFP(left_value, Type::getDoubleTy(*context));
                auto value = builder->CreateFAdd(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isIntegerTy()))
            {
                right_value = builder->CreateSIToFP(right_value, Type::getDoubleTy(*context));
                auto value = builder->CreateFAdd(left_value, right_value, "");
                return value;
            }
            else if ((left_type->isDoubleTy()) && (right_type->isDoubleTy()))
            {
                auto value = builder->CreateFAdd(left_value, right_value, "");
                return value;
            }

            throw std::runtime_error("addidtion operation not supproted now.");
        }
    }
}