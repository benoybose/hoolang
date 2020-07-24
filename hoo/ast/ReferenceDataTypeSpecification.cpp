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

#include <hoo/ast/ReferenceDataTypeSpecification.hh>

namespace hoo
{
    namespace ast
    {
        ReferenceDataTypeSpecification::ReferenceDataTypeSpecification(const std::string &name,
                                                                       std::shared_ptr<TypeSpecification> parent)
            : TypeSpecification(TYPE_SPEC_REFERENCE),
              _name(name),
              _parent(parent),
              _full_name("")
        {
            std::string full_name;
            if (_parent)
            {
                full_name += this->_parent->GetName();
                full_name += ".";
            }

            full_name += this->_name;
            this->_full_name = full_name;
        }

        const std::string &ReferenceDataTypeSpecification::GetName() const
        {
            return this->_full_name;
        }

        std::shared_ptr<TypeSpecification> ReferenceDataTypeSpecification::GetParent()
        {
            return _parent;
        }

        const bool ReferenceDataTypeSpecification::Equals(const TypeSpecification &other)
        {
            if (!TypeSpecification::Equals(other))
            {
                return false;
            }

            auto p_other = &other;
            auto ref_other = static_cast<const ReferenceDataTypeSpecification*>(p_other);
            return (this->_full_name == ref_other->_full_name);
        }

        ReferenceDataTypeSpecification::~ReferenceDataTypeSpecification()
        {
        }
    } // namespace ast
} // namespace hoo
