#include <hoo/ast/CastExpression.hh>
#include <hoo/ast/BasicTypeSpec.hh>

#include <string>
#include <memory>

namespace hoo
{
    namespace ast
    {
        CastExpression::CastExpression(std::shared_ptr<TypeSpecification> type_spec,
        std::shared_ptr<Expression> expr) :
        _type_spec(type_spec),
        _expression(expr),
        _type_spec_type(type_spec->GetType()),
        Expression(EXPRESSION_CAST, type_spec)
        {
        }

        std::shared_ptr<TypeSpecification> CastExpression::GetType()
        {
            return _type_spec;
        }
            
        std::shared_ptr<Expression> CastExpression::GetSourceExpression()
        {
            return _expression;
        }

        bool CastExpression::IsBasicType()
        {
            return _type_spec_type == TYPE_SPEC_BASIC;
        }

        BasicDataTypeType CastExpression::GetBasicDataType()
        {
            if (!IsBasicType())
            {
                return BASIC_DATA_TYPE_INVALID;
            }

            auto basic_type = dynamic_pointer_cast<BasicTypeSpec>(_type_spec);
            return basic_type->GetDataType();
        }
    }
}