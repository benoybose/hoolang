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
#include <hoo/parser/visitors/TypeSpecificationVisitor.hh>
#include <hoo/parser/visitors/ExpressionVisitor.hh>

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
            Declaration* declaration = nullptr;
            DeclaratorType declarator_label = DECLARATOR_NONE;
            auto declarator = ctx->Declarator();
            if (nullptr != declarator)
            {
                auto declarator_text = declarator->getText();
                declarator_label = VisitorHelper::GetDeclarator(declarator_text);
            }

            auto name = ctx->name->getText();
            shared_ptr<TypeSpecification> declared_type = nullptr;
            if (nullptr != ctx->declared_type)
            {
                try
                {
                    TypeSpecificationVisitor type_spec_visitor(_error_listener);
                    auto type_spec = type_spec_visitor.visit(ctx->declared_type)
                                         .as<TypeSpecification *>();
                    declared_type = std::shared_ptr<TypeSpecification>(type_spec);
                }
                catch (...)
                {
                    _error_listener->Add(ctx->declared_type,
                                         "Invalid declared type in variable declaration.");
                }
            }

            shared_ptr<Expression> initializer = nullptr;
            if (nullptr != ctx->init)
            {
                try
                {
                    ExpressionVisitor expression_visitor(_error_listener);
                    auto expr = expression_visitor.visit(ctx->init)
                                    .as<Expression *>();
                    initializer = std::shared_ptr<Expression>(expr);
                }
                catch (...)
                {
                    _error_listener->Add(ctx,
                                         "Invalid initializer on variable declaration.");
                }
            }

            if ((!declared_type) && (!initializer))
            {
                _error_listener->Add(ctx,
                                     "Invalid variable declaration. Type of the variable cannot be inferenced.");
            }

            declaration = new VariableDeclaration(declarator_label, name,
                                                       declared_type, initializer);
            return Any(declaration);
        }
    } // namespace parser
} // namespace hoo