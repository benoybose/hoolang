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
#include <hoo/parser/visitors/StatementVisitor.hh>
#include <hoo/parser/visitors/VariableDeclarationVisitor.hh>
#include <hoo/parser/visitors/FunctionDefinitionVisitor.hh>
#include <hoo/parser/ErrorListener.hh>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        StatementVisitor::StatementVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any StatementVisitor::visitNoOpStatement(HooParser::NoOpStatementContext *ctx)
        {
            Statement *statement = new NoopStatement();
            return Any(statement);
        }

        Any StatementVisitor::visitCompoundStatement(HooParser::CompoundStatementContext *ctx)
        {
            auto statements = ctx->statement();
            std::list<std::shared_ptr<Statement>> statement_list;

            for (auto statement_ctx : statements)
            {
                std::shared_ptr<Statement> statement;
                try
                {
                    auto stmt = this->visit(statement_ctx).as<Statement *>();
                    statement = std::shared_ptr<Statement>(stmt);
                }
                catch (...)
                {
                    _error_listener->Add(statement_ctx, "Invalid statement inside a compound statement.");
                    continue;
                }

                if (statement)
                {
                    statement_list.push_back(statement);
                }
                else
                {
                    _error_listener->Add(statement_ctx, "Failed to parse a statement inside a compound statement.");
                }
            }

            Statement *compound_statement = new CompoundStatement(statement_list);
            return Any(compound_statement);
        }

        Any StatementVisitor::visitReturnStatement(HooParser::ReturnStatementContext *ctx)
        {
            if (nullptr == ctx->returnValue)
            {
                return Any(new ReturnStatement());
            }
            else
            {
                std::shared_ptr<Expression> return_expr;
                try
                {
                    auto expression = this->visit(ctx->returnValue)
                                          .as<Expression *>();
                    return_expr = std::shared_ptr<Expression>(expression);
                }
                catch (...)
                {
                    _error_listener->Add(ctx, "Invalid expression on return statement.");
                }

                Statement *statement = new ReturnStatement(return_expr);
                return Any(statement);
            }
        }

        Any StatementVisitor::visitExpressionStatement(HooParser::ExpressionStatementContext *ctx)
        {
            Statement *statement = nullptr;
            try
            {
                auto expr_ctx = ctx->expression();
                auto expression = this->visit(expr_ctx)
                                      .as<Expression *>();
                auto expr = std::shared_ptr<Expression>(expression);
                statement = new ExpressionStatement(expr);
            }
            catch (...)
            {
                _error_listener->Add(ctx,
                                     "Invalid expression, while parsing an expression statement.");
            }
            return Any(statement);
        }

        Any StatementVisitor::visitDeclarationStatement(HooParser::DeclarationStatementContext *ctx)
        {
            auto var_decl_context = ctx->variableDeclaration();
            Statement *statement = nullptr;
            if (nullptr != var_decl_context)
            {
                try
                {
                    VariableDeclarationVisitor var_decl_visitor(_error_listener);
                    auto var_decl = var_decl_visitor.visit(var_decl_context)
                                        .as<VariableDeclaration *>();
                    std::shared_ptr<Declaration> declaration = std::shared_ptr<Declaration>(var_decl);
                    statement = new DeclarationStatement(declaration);
                }
                catch (...)
                {
                    _error_listener->Add(var_decl_context,
                                         "Invalid variable declaration while parsing a declaration statement.");
                }
            }
            else
            {
                auto func_decl_context = ctx->functionDeclaration();
                if (nullptr == func_decl_context)
                {
                    try
                    {
                        FunctionDefinitionVisitor func_decl_visitor(_error_listener);
                        auto func_decl = func_decl_visitor.visit(func_decl_context)
                                             .as<FunctionDeclaration *>();
                        std::shared_ptr<Declaration> declaration = std::shared_ptr<Declaration>(func_decl);
                        statement = new DeclarationStatement(declaration);
                    }
                    catch (...)
                    {
                        _error_listener->Add(func_decl_context,
                                             "Invalid function declaration while parsing a declaration statement.");
                    }
                }
                else
                {
                    _error_listener->Add(ctx, "Invalid declaration statement.");
                }
            }
            return Any(statement);
        }
    } // namespace parser
} // namespace hoo