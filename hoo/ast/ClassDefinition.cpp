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

#include <hoo/ast/ClassDefinition.hh>

namespace hoo
{
    namespace ast
    {
        ClassDefinition::ClassDefinition(std::string &class_name,
                                         std::list<std::string> &base_entities,
                                         std::shared_ptr<ClassBody> &body)
            : Definition(DEFINITION_CLASS),
              _class_name(std::move(class_name)),
              _base_entities(base_entities),
              _body(body)
        {
        }

        const std::string &ClassDefinition::GetClassName() const
        {
            return this->_class_name;
        }

        const bool ClassDefinition::IsEmpty() const
        {
            if (!this->_body)
            {
                return true;
            }
            return this->_body->IsEmpty();
        }

        const std::list<std::string> &ClassDefinition::GetBaseEntities() const
        {
            return this->_base_entities;
        }

        const bool ClassDefinition::HasBaseEntities() const
        {
            auto base_entities = this->GetBaseEntities();
            return (0 < base_entities.size());
        }
    } // namespace ast
} // namespace hoo
