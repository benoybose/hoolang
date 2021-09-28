/*
 * Copyright 2020 Benoy Bose
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

#include <hoo/ast/Expression.hh>
#include <hoo/ast/BasicDataTypes.hh>
#include <hoo/ast/BasicTypeSpec.hh>

#include <memory>

namespace hoo
{
    namespace ast
    {
        Expression::Expression(ExpressionType expressionType,
                               std::shared_ptr<TypeSpecification> type)
            : _expressionType(expressionType),
              _type(type)
        {
        }

        Expression::~Expression()
        {
        }

        const ExpressionType Expression::GetExpressionType() const
        {
            return this->_expressionType;
        }

        std::shared_ptr<TypeSpecification> Expression::GetType()
        {
            return this->_type;
        }

        bool Expression::IsBasicType()
        {
            if (!_type)
            {
                return false;
            }

            return TYPE_SPEC_BASIC == _type->GetType();
        }

        BasicDataTypeType Expression::GetBasicDataType()
        {
            if (!IsBasicType())
            {
                return BASIC_DATA_TYPE_INVALID;
            }

            auto basic_type = dynamic_pointer_cast<BasicTypeSpec>(_type);
            return basic_type->GetDataType();
        }
    } // namespace ast
} // namespace hoo