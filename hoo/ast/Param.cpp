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

#include <hoo/ast/Param.hh>

namespace hoo
{
    namespace ast
    {
        Param::Param(size_t position,
                     std::shared_ptr<StorageItem> storage_item)
            : _position(position),
              _storage_item(storage_item)
        {
        }

        const size_t Param::GetPosition() const
        {
            return this->_position;
        }

        const std::string &Param::GetName() const
        {
            return this->_storage_item->GetName();
        }

        std::shared_ptr<TypeSpecification> Param::GetType()
        {
            return this->_storage_item->GetType();
        }

        std::shared_ptr<Expression> Param::GetInitializer()
        {
            return this->_storage_item->GetInitializer();
        }

        bool Param::IsOptional()
        {
            auto initializer = this->GetInitializer();
            if (initializer)
            {
                return true;
            }
            return false;
        }
    } // namespace ast
} // namespace hoo