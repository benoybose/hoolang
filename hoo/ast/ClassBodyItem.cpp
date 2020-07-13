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

#include <hoo/ast/ClassBodyItem.hh>

namespace hoo
{
    namespace ast
    {
        ClassBodyItem::ClassBodyItem(std::shared_ptr<FunctionDefinition> &funcdef)
            : _class_body_type(CLSBODY_FUNCTIONDEF),
              _function_def(std::move(funcdef))
        {
        }

        ClassBodyItem::ClassBodyItem(std::shared_ptr<DeclarationStatement> &declstmt)
            : _class_body_type(CLSBODY_DECLARATIONSTMT),
              _declaration_stmt(std::move(declstmt))
        {
        }

        ClassBodyItemType ClassBodyItem::GetType()
        {
            return this->_class_body_type;
        }

        std::shared_ptr<FunctionDefinition> &ClassBodyItem::GetFunctionDefinition()
        {
            return this->_function_def;
        }

        std::shared_ptr<DeclarationStatement> &ClassBodyItem::GetDeclarationStatement()
        {
            return this->_declaration_stmt;
        }
    } // namespace ast
} // namespace hoo