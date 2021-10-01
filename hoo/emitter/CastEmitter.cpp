#include <hoo/emitter/CastEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/ExpressionEmitter.hh>
#include <hoo/emitter/EmitterUtils.hh>
#include <hoo/ast/CastExpression.hh>
#include <hoo/ast/BasicDataTypes.hh>
#include <hoo/ast/BasicTypeSpec.hh>

#include <memory>

namespace hoo
{
    namespace emitter
    {
        CastEmitter::CastEmitter(const std::shared_ptr<CastExpression> &cast_expression,
                                 const EmitterContext &emittter_context) : _expression(cast_expression),
                                                                           _source_expression(cast_expression->GetSourceExpression()),
                                                                           EmitterBase(emittter_context),
                                                                           _source_value(nullptr),
                                                                           _source_basic_type(BASIC_DATA_TYPE_INVALID)
        {
            ExpressionEmitter emitter(_source_expression, emittter_context);
            _source_value = emitter.Emit();
            _source_basic_type = EmitterUtils::GetBasicDataType(_source_value);
        }

        bool CastEmitter::IsBasicType()
        {
            return _source_basic_type != BASIC_DATA_TYPE_INVALID;
        }

        Value *CastEmitter::Emit()
        {
            if ((_expression->IsBasicType()) && (IsBasicType()))
            {
                auto value = EmitCastBasicDataTypes();
                return value;
            }
            else
            {
                auto value = EmitCastReferenceTypes();
                return value;
            }
        }

        Value *CastEmitter::EmitCastBasicDataTypes()
        {
            auto dest_type = _expression->GetBasicDataType();
            switch (dest_type)
            {
            case BASIC_DATA_TYPE_BYTE:
                return CastToByte();

            case BASIC_DATA_TYPE_INT:
                return CastToInt();

            case BASIC_DATA_TYPE_DOUBLE:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

            case BASIC_DATA_TYPE_BOOL:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

            case BASIC_DATA_TYPE_CHAR:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

            case BASIC_DATA_TYPE_STRING:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);
            }
        }

        Value *CastEmitter::EmitCastReferenceTypes()
        {
            throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING, ERR_POS(_expression));
        }

        Value *CastEmitter::CastToByte()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            auto byte_type = Type::getInt8Ty(*context);

            switch (_source_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));
            case BASIC_DATA_TYPE_BYTE:
                return _source_value;
            case BASIC_DATA_TYPE_CHAR:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));
            case BASIC_DATA_TYPE_DOUBLE:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));
            case BASIC_DATA_TYPE_INT:
            {
                auto value = builder->CreateCast(Instruction::Trunc, _source_value, byte_type);
                return value;
            }
            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));
            case BASIC_DATA_TYPE_STRING:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));
            }
            return nullptr;
        }

        Value *CastEmitter::CastToInt()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();
            auto int_type = Type::getInt64Ty(*context);

            switch (_source_basic_type)
            {
            case BASIC_DATA_TYPE_BOOL:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));

            case BASIC_DATA_TYPE_BYTE:
            {
                auto value = builder->CreateCast(Instruction::SExt, _source_value, int_type);
                return value;
            }

            case BASIC_DATA_TYPE_CHAR:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));

            case BASIC_DATA_TYPE_DOUBLE:
            {
                auto value = builder->CreateFPToSI(_source_value, int_type);
                return value;
            }

            case BASIC_DATA_TYPE_INT:
                return _source_value;

            case BASIC_DATA_TYPE_INVALID:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));

            case BASIC_DATA_TYPE_STRING:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));

            default:
                throw EmitterException(ERR_EMITTER_INVALID_CAST, ERR_POS(_expression));
            }
        }
    }
}