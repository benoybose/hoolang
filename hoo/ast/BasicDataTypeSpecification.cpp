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

#include <hoo/ast/BasicDataTypeSpecification.hh>
#include <hoo/ast/BasicDataTypes.hh>

namespace hoo {
    namespace ast {

        BasicDataTypeSpecification::BasicDataTypeSpecification(BasicDataTypeType data_type) :
                TypeSpecification(TYPE_SPEC_BASIC),
                _data_type(data_type) {
        }

        BasicDataTypeType BasicDataTypeSpecification::GetDataType() const {
            return _data_type;
        }

        const std::string &BasicDataTypeSpecification::GetName() const {
            return GetBasicDataTypeName(this->_data_type);
        }

        const bool BasicDataTypeSpecification::Equals(const TypeSpecification &other)
        {
            if (!TypeSpecification::Equals(other))
            {
                return false;
            }
            auto p_other = &other;
            auto basic_type = static_cast<const BasicDataTypeSpecification*>(p_other);
            return this->_data_type == basic_type->_data_type;
        }

        BasicDataTypeSpecification::~BasicDataTypeSpecification() {
        }
    }
}
