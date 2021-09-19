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

#include "HooBaseVisitor.h"
#include "ParserRuleContext.h"

#include <hoo/parser/visitors/VisitorHelper.hh>
#include <hoo/parser/visitors/ExpressionVisitor.hh>

#include <memory>

using namespace antlr4;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        DeclaratorType VisitorHelper::GetDeclarator(const std::string &declarator)
        {
            if (declarator.empty())
            {
                return DECLARATOR_NONE;
            }
            else if (declarator == "public")
            {
                return DECLARATOR_PUBLIC;
            }
            else if (declarator == "private")
            {
                return DECLARATOR_PRIVATE;
            }
            else if (declarator == "protected")
            {
                return DECLARATOR_PROTECTED;
            }
            else
            {
                return DECLARATOR_INVALID;
            }
        }

        void VisitorHelper::AssignPositions(Node *node, ParserRuleContext *context)
        {
            auto start = context->getStart();
            auto start_pos = std::make_shared<Position>(start->getLine(),
            start->getCharPositionInLine());
            auto end = context->getStop();
            auto end_pos = std::make_shared<Position>(end->getLine(),
            end->getCharPositionInLine());
            node->SetStart(start_pos);
            node->SetEnd(end_pos);
        }
    } // namespace parser
} // namespace hoo