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

#ifndef PROJECT_DECLARATION_HH
#define PROJECT_DECLARATION_HH

#include <hoo/ast/Declaration.hh>
#include <hoo/ast/Declarator.hh>
#include <hoo/ast/TypeSpecification.hh>
#include <hoo/ast/Expression.hh>
#include <hoo/ast/StorageItem.hh>

#include <string>
#include <memory>

namespace hoo
{
    namespace ast
    {
        typedef enum
        {
            LOCAL_ITEM_VARIABLE,
            LOCAL_ITEM_CONSTANT
        } LocalItemType;

        class ItemDeclaration : public Declaration
        {
        private:
            LocalItemType _local_item_type;
            std::shared_ptr<StorageItem> _storage;

        public:
            ItemDeclaration(LocalItemType local_item_type,
                                std::shared_ptr<StorageItem> storage);

        public:
            const DeclaratorType GetDeclarator() const;
            const std::string &GetName() const;
            std::shared_ptr<TypeSpecification> GetDelcaredType();
            std::shared_ptr<Expression> GetInitializer();

        public:
            virtual ~ItemDeclaration();
        };
    } // namespace ast
} // namespace hoo

#endif //PROJECT_DECLARATION_HH
