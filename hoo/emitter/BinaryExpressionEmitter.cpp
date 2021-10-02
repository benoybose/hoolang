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

#include <hoo/emitter/BinaryExpressionEmitter.hh>
#include <hoo/emitter/ExpressionEmitter.hh>
#include <hoo/emitter/EmitterContext.hh>
#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/emitter/EmitterException.hh>

namespace hoo
{
    namespace emitter
    {
        BinaryExpressionEmitter::BinaryExpressionEmitter(std::shared_ptr<BinaryExpression> binary_expression,
                                                         const EmitterContext &emitter_context) : _binary_expression(binary_expression),
                                                                                                  _left_expression(binary_expression->GetLeftExpression()),
                                                                                                  _right_expression(binary_expression->GetRightExpression()),
                                                                                                  _operator(binary_expression->GetOperator()),
                                                                                                  _left_value(nullptr),
                                                                                                  _right_value(nullptr),
                                                                                                  EmitterBase(emitter_context)
        {
            ExpressionEmitter left_emitter(_left_expression, emitter_context);
            _left_value = left_emitter.Emit();
            _left_type = _left_value->getType();

            ExpressionEmitter right_emitter(_right_expression, emitter_context);
            _right_value = right_emitter.Emit();
            _right_type = _right_value->getType();

            _left_basic_type = EmitterUtils::GetBasicDataType(_left_value);
            _right_basic_type = EmitterUtils::GetBasicDataType(_right_value);
        }

        bool BinaryExpressionEmitter::IsBothBasicDataType()
        {
            return (_left_basic_type != BASIC_DATA_TYPE_INVALID) &&
                   (_right_basic_type != BASIC_DATA_TYPE_INVALID);
        }

        Value *BinaryExpressionEmitter::Emit()
        {
            if (!_left_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_LEFT_EXPRESSION, ERR_POS(_left_expression));
            }

            if (!_right_value)
            {
                throw EmitterException(ERR_EMITTER_FAILED_RIGHT_EXPRESSION, ERR_POS(_right_expression));
            }

            auto const operator_type = _operator->GetOperatorType();
            auto value = EmitOperation(operator_type);
            return value;
        }

        Value *BinaryExpressionEmitter::EmitOperation(const OperatorType operator_type)
        {
            switch (operator_type)
            {
            case OPERATOR_ADD:
                return EmitAdd();
            case OPERATOR_SUB:
                return EmitSub();
            default:
                throw EmitterException(ERR_EMITTER_BINARY_FAILED_EXPRESSION, ERR_POS(_binary_expression));
            }
        }

        Value *BinaryExpressionEmitter::EmitAdd()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();

            if (!IsBothBasicDataType())
            {
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
            else
            {
                switch (_left_basic_type)
                {
                case BASIC_DATA_TYPE_INT:
                    return EmitAddToInt(builder, context);
                case BASIC_DATA_TYPE_DOUBLE:
                    return EmitAddToDouble(builder, context);
                case BASIC_DATA_TYPE_BYTE:
                    return EmitAddToByte(builder, context);
                default:
                    throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
                }
            }

            throw EmitterException(ERR_EMITTER_SUB_OPERATION_UNSUPPORTED, ERR_POS(_binary_expression));
        }

        Value *BinaryExpressionEmitter::EmitAddToInt(IRBuilder<> *builder, LLVMContext *context)
        {
            switch (_right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(_binary_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto right_value = builder->CreateZExt(_right_value, Type::getInt64Ty(*context));
                auto value = builder->CreateNSWAdd(_left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto left_value = builder->CreateSIToFP(_left_value, Type::getDoubleTy(*context));
                auto value = builder->CreateFAdd(left_value, _right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto value = builder->CreateNSWAdd(_left_value, _right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
        }

        Value *BinaryExpressionEmitter::EmitAddToDouble(IRBuilder<> *builder, LLVMContext *context)
        {
            auto double_type = Type::getDoubleTy(*context);
            switch (_right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(_binary_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto right_value = builder->CreateZExt(_right_value, Type::getInt64Ty(*context));
                right_value = builder->CreateSIToFP(right_value, double_type);
                auto value = builder->CreateFAdd(_left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto value = builder->CreateFAdd(_left_value, _right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto right_value = builder->CreateSIToFP(_right_value, double_type);
                auto value = builder->CreateFAdd(_left_value, right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
        }

        Value *BinaryExpressionEmitter::EmitAddToByte(IRBuilder<> *builder, LLVMContext *context)
        {
            auto int_type = Type::getInt64Ty(*context);
            auto byte_type = Type::getInt8Ty(*context);
            auto double_type = Type::getDoubleTy(*context);

            switch (_right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(_binary_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto left_value = builder->CreateCast(Instruction::ZExt, _left_value, int_type);
                auto right_value = builder->CreateCast(Instruction::ZExt, _right_value, int_type);
                auto value = builder->CreateAdd(left_value, right_value);
                value = builder->CreateTrunc(value, byte_type);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto left_value = builder->CreateCast(Instruction::ZExt, _left_value, int_type);
                left_value = builder->CreateSIToFP(left_value, double_type);
                auto value = builder->CreateFAdd(left_value, _right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto left_value = builder->CreateCast(Instruction::ZExt, _left_value, int_type);
                auto value = builder->CreateNSWAdd(left_value, _right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
        }

        Value *BinaryExpressionEmitter::EmitSub()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();

            if (!IsBothBasicDataType())
            {
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
            else
            {
                switch (_left_basic_type)
                {
                case BASIC_DATA_TYPE_INT:
                    return EmitSubFromInt();
                case BASIC_DATA_TYPE_DOUBLE:
                    return EmitSubFromDouble();
                case BASIC_DATA_TYPE_BYTE:
                    return EmitSubFromByte();
                default:
                    throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
                }
            }

            throw EmitterException(ERR_EMITTER_SUB_OPERATION_UNSUPPORTED, ERR_POS(_binary_expression));
        }

        Value *BinaryExpressionEmitter::EmitSubFromInt()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            switch (_right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(_binary_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto right_value = builder->CreateZExt(_right_value, Type::getInt64Ty(*context));
                auto value = builder->CreateNSWSub(_left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto left_value = builder->CreateSIToFP(_left_value, Type::getDoubleTy(*context));
                auto value = builder->CreateFSub(left_value, _right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto value = builder->CreateNSWSub(_left_value, _right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
        }

        Value *BinaryExpressionEmitter::EmitSubFromDouble()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            auto double_type = Type::getDoubleTy(*context);

            switch (_right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(_binary_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto right_value = builder->CreateZExt(_right_value, Type::getInt64Ty(*context));
                right_value = builder->CreateSIToFP(right_value, double_type);
                auto value = builder->CreateFSub(_left_value, right_value);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto value = builder->CreateFSub(_left_value, _right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto right_value = builder->CreateSIToFP(_right_value, double_type);
                auto value = builder->CreateFSub(_left_value, right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
        }

        Value *BinaryExpressionEmitter::EmitSubFromByte()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            auto int_type = Type::getInt64Ty(*context);
            auto byte_type = Type::getInt8Ty(*context);
            auto double_type = Type::getDoubleTy(*context);
            switch (_right_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
            case BASIC_DATA_TYPE_CHAR:
            case BASIC_DATA_TYPE_STRING:
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_SUB, ERR_POS(_binary_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto left_value = builder->CreateCast(Instruction::ZExt, _left_value, int_type);
                auto right_value = builder->CreateCast(Instruction::ZExt, _right_value, int_type);
                auto value = builder->CreateSub(left_value, right_value);
                value = builder->CreateTrunc(value, byte_type);
                return value;
            }
            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto left_value = builder->CreateCast(Instruction::ZExt, _left_value, int_type);
                left_value = builder->CreateSIToFP(left_value, double_type);
                auto value = builder->CreateFSub(left_value, _right_value);
                return value;
            }
            case BASIC_DATA_TYPE_INT:
            {
                auto left_value = builder->CreateCast(Instruction::ZExt, _left_value, int_type);
                auto value = builder->CreateNSWSub(left_value, _right_value);
                return value;
            }
            default:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_binary_expression));
            }
        }
    }
}
