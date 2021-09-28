#include <hoo/emitter/CastEmitter.hh>
#include <hoo/emitter/EmitterException.hh>
#include <hoo/emitter/ExpressionEmitter.hh>
#include <hoo/ast/CastExpression.hh>
#include <hoo/ast/BasicDataTypes.hh>
#include <hoo/ast/BasicTypeSpec.hh>

#include <memory>

namespace hoo
{
    namespace emitter
    {
        CastEmitter::CastEmitter(const std::shared_ptr<CastExpression> &cast_expression,
            const EmitterContext& emittter_context) :
        _expression(cast_expression),
        _source_expression(cast_expression->GetSourceExpression()),
        EmitterBase(emittter_context),
        _source_value(nullptr),
        _basic_data_type(BASIC_DATA_TYPE_INVALID)
        {
            ExpressionEmitter emitter(_source_expression, emittter_context);
            _source_value = emitter.Emit();
            auto _source_value_type = _source_value->getType();
            if (_source_value_type->isIntegerTy(64))
            {
                _basic_data_type = BASIC_DATA_TYPE_INT;
            }
            else if (_source_value_type->isIntegerTy(8))
            {
                _basic_data_type = BASIC_DATA_TYPE_BYTE;
            }
            else if (_source_value_type->isIntegerTy(1))
            {
                _basic_data_type = BASIC_DATA_TYPE_BOOL;
            }
            else if (_source_value_type->isDoubleTy())
            {
                _basic_data_type = BASIC_DATA_TYPE_DOUBLE;
            }
        }

        bool CastEmitter::IsBasicType()
        {
            return _basic_data_type != BASIC_DATA_TYPE_INVALID;
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
            switch(dest_type)
            {
                case BASIC_DATA_TYPE_BYTE:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

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

        Value *CastEmitter::CastToInt()
        {
            auto builder = _emitter_context.GetBuilder();
            auto context = _emitter_context.GetContext();

            switch(_basic_data_type)
            {
                case BASIC_DATA_TYPE_BYTE:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

                case BASIC_DATA_TYPE_INT:
                throw EmitterException(ERR_EMITTER_NOT_IMPLEMENTED_EMITTING);

                case BASIC_DATA_TYPE_DOUBLE:
                {
                    auto value = builder->CreateFPToSI(_source_value,
                    Type::getInt64Ty(*context));
                    return value;
                }

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
    }
}