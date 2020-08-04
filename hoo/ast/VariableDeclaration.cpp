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

#include <hoo/ast/VariableDeclaration.hh>

namespace hoo
{
    namespace ast
    {
        VariableDeclaration::VariableDeclaration(LocalItemType local_item_type,
                                                 std::shared_ptr<StorageItem> storage)
            : Declaration(DECLARATION_LOCAL_ITEM, DECLARATOR_NONE),
              _local_item_type(local_item_type),
              _storage(storage)
        {
        }

        const DeclaratorType VariableDeclaration::GetDeclarator() const
        {
            return Declaration::GetDeclarator();
        }

        const std::string &VariableDeclaration::GetName() const
        {
            return this->_storage->GetName();
        }

        std::shared_ptr<TypeSpecification> VariableDeclaration::GetDelcaredType()
        {
            return this->_storage->GetType();
        }

        std::shared_ptr<Expression> VariableDeclaration::GetInitializer()
        {
            return this->_storage->GetInitializer();
        }

        VariableDeclaration::~VariableDeclaration()
        {
        }
    } // namespace ast
} // namespace hoo
