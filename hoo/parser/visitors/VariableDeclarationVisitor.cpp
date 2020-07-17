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

#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/VariableDeclarationVisitor.hh>
#include <hoo/parser/ErrorListener.hh>
#include <hoo/parser/visitors/VisitorHelper.hh>

#include <memory>

using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        VariableDeclarationVisitor::VariableDeclarationVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any VariableDeclarationVisitor::visitVariableDeclaration(HooParser::VariableDeclarationContext *ctx)
        {
            DeclaratorType declarator_label = DECLARATOR_NONE;
            auto declarator = ctx->Declarator();
            if (nullptr != declarator)
            {
                auto declarator_text = declarator->getText();
                declarator_label = VistorHelper::GetDeclarator(declarator_text);
            }

            auto name = ctx->name->getText();
            auto declared_type = this->visit(ctx->declared_type).as<TypeSpecification *>();
            Expression *initializer = nullptr;
            if (nullptr != ctx->init)
            {
                initializer = this->visit(ctx->init).as<Expression *>();
            }

            auto declaration = new VariableDeclaration(declarator_label, name,
                                                       declared_type, initializer);
            return Any(declaration);
        }

        Any VariableDeclarationVisitor::visitMultipleItemParamList(HooParser::MultipleItemParamListContext *ctx)
        {
            auto param_list = this->visit(ctx->list)
                                  .as<std::list<std::shared_ptr<VariableDeclaration>>>();
            auto declarations = ctx->variableDeclaration();
            for (auto declaration : declarations)
            {
                auto item = this->visit(declaration).as<VariableDeclaration *>();
                param_list.push_back(std::shared_ptr<VariableDeclaration>(item));
            }
            return Any(param_list);
        }

        Any VariableDeclarationVisitor::visitSingleItemParamList(HooParser::SingleItemParamListContext *ctx)
        {
            auto declaration = this->visit(ctx->decl).as<VariableDeclaration *>();
            std::list<std::shared_ptr<VariableDeclaration>> param_list;
            param_list.push_back(shared_ptr<VariableDeclaration>(declaration));
            return Any(param_list);
        }
    } // namespace parser
} // namespace hoo