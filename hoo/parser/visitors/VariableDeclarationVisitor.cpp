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
            const std::string local_type_spec = ctx->type->getText();
            auto local_item_type = LOCAL_ITEM_VARIABLE;
            if (local_type_spec == "let")
            {
                local_item_type = LOCAL_ITEM_VARIABLE;
            }

            std::shared_ptr<StorageItem> storage;
            try
            {
                auto storage_decl = this->visit(ctx->decl)
                                        .as<StorageItem *>();
                storage = std::shared_ptr<StorageItem>(storage_decl);
            }
            catch (...)
            {
                this->_error_listener->Add(ctx->decl, "Invalid storage declaration.");
            }

            auto local_item_declaration = new VariableDeclaration(local_item_type, storage);
            return Any(local_item_declaration);
        }

        Any VariableDeclarationVisitor::visitTypedStorageItem(HooParser::TypedStorageItemContext *ctx)
        {
            auto name = ctx->name->getText();

            std::shared_ptr<TypeSpecification> type;
            try
            {
                TypeSpecificationVisitor type_spec_visitor(_error_listener);
                auto type_spec = type_spec_visitor.visit(ctx->declared_type)
                                     .as<TypeSpecification *>();
                type = std::shared_ptr<TypeSpecification>(type_spec);
            }
            catch (...)
            {
                this->_error_listener->Add(ctx->declared_type, "Invalid type specification for storage item.");
            }

            std::shared_ptr<Expression> expression;
            if (nullptr != ctx->init)
            {
                try
                {
                    ExpressionVisitor expression_visitor(_error_listener);
                    auto expr = expression_visitor.visit(ctx->init)
                                    .as<Expression *>();
                    expression = std::shared_ptr<Expression>(expr);
                }
                catch (...)
                {
                    _error_listener->Add(ctx->init, "Invalid initializer on variable declaration.");
                }
            }

            auto storage_declaration = new StorageItem(name, type, expression);
            return Any(storage_declaration);
        }

        Any VariableDeclarationVisitor::visitStorageItem(HooParser::StorageItemContext *ctx)
        {
            auto typed_storage_ctx = ctx->typedStorageItem();
            if (nullptr != typed_storage_ctx)
            {
                auto storage = this->visit(typed_storage_ctx)
                                   .as<StorageItem *>();
                return Any(storage);
            }

            const auto name = ctx->name->getText();
            std::shared_ptr<StorageItem> storage;
            try
            {
                ExpressionVisitor visitor(_error_listener);
                auto expression = visitor.visit(ctx->init)
                                      .as<Expression *>();
                auto type = expression->GetType();
                std::shared_ptr<Expression> initializer = std::shared_ptr<Expression>(expression);
                storage = std::shared_ptr<StorageItem>(new StorageItem(name, type, initializer));
            }
            catch (...)
            {
                this->_error_listener->Add(ctx->init, "Invalid initializing expression on storage declaration.");
            }
            return storage;
        }
    } // namespace parser
} // namespace hoo