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
#include <hoo/parser/ErrorListener.hh>
#include <hoo/parser/visitors/ExpressionVisitor.hh>

#include <regex>
#include <list>
#include <memory>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        ExpressionVisitor::ExpressionVisitor(ErrorListener *error_listener)
            : _error_listener(error_listener)
        {
        }

        Any ExpressionVisitor::visitConstantExpression(HooParser::ConstantExpressionContext *ctx)
        {
            Expression *expression = nullptr;
            auto byte_constant_terminal = ctx->ByteContant();
            if (nullptr != byte_constant_terminal)
            {
                auto byte_text = byte_constant_terminal->getText();
                Expression *byte_expression = new LiteralExpression(LITERAL_BYTE,
                                                                    byte_text);
                return Any(byte_expression);
            }

            auto integer_constant_terminal = ctx->IntegerConstant();
            if (nullptr != integer_constant_terminal)
            {
                auto integer_text = integer_constant_terminal->getText();
                Expression *integer_expression = new LiteralExpression(LITERAL_INTEGER,
                                                                       integer_text);
                return Any(integer_expression);
            }

            auto floating_constant_terminal = ctx->FloatingConstant();
            if (nullptr != floating_constant_terminal)
            {
                auto float_text = floating_constant_terminal->getText();
                Expression *fp_expression = new LiteralExpression(LITERAL_DOUBLE,
                                                                  float_text);
                return Any(fp_expression);
            }

            auto char_constant_terminal = ctx->CharacterConstant();
            if (nullptr != char_constant_terminal)
            {
                auto char_text = char_constant_terminal->getText();
                Expression *char_expression = new LiteralExpression(LITERAL_CHARACTER,
                                                                    char_text);
                return Any(char_expression);
            }

            auto bool_constant_terminal = ctx->BooleanConstant();
            if (nullptr != bool_constant_terminal)
            {
                auto bool_text = bool_constant_terminal->getText();
                Expression *bool_expression = new LiteralExpression(LITERAL_BOOLEAN,
                                                                    bool_text);
                return Any(bool_expression);
            }

            _error_listener->Add(ctx,
                                 "Invalid literal expression on constant expression.");
            return Any(expression);
        }

        Any ExpressionVisitor::visitStringExpression(HooParser::StringExpressionContext *ctx)
        {
            auto string_terminal = ctx->StringLiteral();
            auto string_text = string_terminal->getText();
            Expression *expression = new LiteralExpression(LITERAL_STRING, string_text);
            return Any(expression);
        }

        Any ExpressionVisitor::visitIdentifierExpression(HooParser::IdentifierExpressionContext *ctx)
        {
            auto id_terminal = ctx->Identifier();
            auto id_name = id_terminal->getText();
            Expression *expression = new ReferenceExpression(id_name);
            return Any(expression);
        }

        Any ExpressionVisitor::visitSimpleExpression(HooParser::SimpleExpressionContext *ctx)
        {
            Expression *expression = nullptr;
            try
            {
                expression = this->visit(ctx->primaryExpression())
                                 .as<Expression *>();
            }
            catch (...)
            {
                _error_listener->Add(ctx, "Error while parsing simple expression.");
            }
            return expression;
        }

        Any ExpressionVisitor::visitArrayAccessExpression(HooParser::ArrayAccessExpressionContext *ctx)
        {
            std::shared_ptr<Expression> container;
            try
            {
                auto container_exp = this->visit(ctx->container)
                                         .as<Expression *>();
                container = std::shared_ptr<Expression>(container_exp);
            }
            catch (...)
            {
                _error_listener->Add(ctx->container,
                                     "Error while parsing container of array access expression.");
            }

            std::shared_ptr<Expression> access_index;
            try
            {
                auto access_index_exp = this->visit(ctx->accessIndex)
                                            .as<Expression *>();
                access_index = std::shared_ptr<Expression>(access_index_exp);
            }
            catch (...)
            {
                _error_listener->Add(ctx->accessIndex, "Error while parsing index expression of array access expression.");
            }

            Expression *expression = nullptr;
            if ((container) && (access_index))
            {
                expression = (Expression *)new ArrayAccessExpression(container,
                                                                     access_index);
            }

            return Any(expression);
        }

        Any ExpressionVisitor::visitInvokeExpression(HooParser::InvokeExpressionContext *ctx)
        {
            std::shared_ptr<Expression> receiver_expr;
            Expression *expression = nullptr;

            try
            {
                auto receiver = this->visit(ctx->receiver)
                                    .as<Expression *>();
                receiver_expr = std::shared_ptr<Expression>(receiver);
            }
            catch (...)
            {
                _error_listener->Add(ctx,
                                     "Invalid expression on invocation expression.");
            }

            std::list<std::shared_ptr<Expression>> argument_list;
            if (nullptr != ctx->arguments)
            {
                auto arg_ctxs = ctx->arguments->expression();
                for (auto arg_ctx : arg_ctxs)
                {
                    try
                    {
                        auto expr = this->visit(arg_ctx)
                                        .as<Expression *>();
                        auto arg = std::shared_ptr<Expression>(expr);
                        argument_list.push_back(arg);
                    }
                    catch (...)
                    {
                        _error_listener->Add(arg_ctx,
                                             "Invalid expression as argument for invocation.");
                    }
                }
            }

            if (receiver_expr)
            {
                expression = new InvokeExpression(receiver_expr,
                                                  argument_list);
            }
            else
            {
                _error_listener->Add(ctx, "Invalid invocation expression.");
            }

            return Any(expression);
        }

        Any ExpressionVisitor::visitNestedExpression(HooParser::NestedExpressionContext *ctx)
        {
            std::shared_ptr<Expression> parent;
            try
            {
                auto parent_expr = this->visit(ctx->parent).as<Expression *>();
                parent = std::shared_ptr<Expression>(parent_expr);
            }
            catch (...)
            {
                _error_listener->Add(ctx->parent,
                                     "Invalid expression on nested reference expression.");
            }

            std::string name = "";
            if (nullptr != ctx->name)
            {
                name = ctx->name->getText();
            }
            else
            {
                _error_listener->Add(ctx, "Invalid name on nested reference expression.");
            }

            Expression *expression = new ReferenceExpression(parent, name);
            return Any(expression);
        }

        Any ExpressionVisitor::visitBinaryBitExpression(HooParser::BinaryBitExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any(expr);
        }

        Any ExpressionVisitor::visitBinaryAddExpression(HooParser::BinaryAddExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any(expr);
        }

        Any ExpressionVisitor::visitBinaryMultiplicateExpression(
            HooParser::BinaryMultiplicateExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any(expr);
        }

        Any ExpressionVisitor::visitBinaryCompareExpression(
            HooParser::BinaryCompareExpressionContext *ctx)
        {
            auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitBinaryLogicExpression(HooParser::BinaryLogicExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                                      ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitBinaryAssignmentExpression(
            HooParser::BinaryAssignmentExpressionContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                                      ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitGroupedExpression(HooParser::GroupedExpressionContext *ctx)
        {
            auto expression = this->visit(ctx->expression())
                                  .as<Expression *>();
            return Any(expression);
        }

        Expression *ExpressionVisitor::CreateBinaryExpression(HooParser::ExpressionContext *lvalue,
                                                              antlr4::Token *opr,
                                                              HooParser::ExpressionContext *rvalue,
                                                              ParserRuleContext *context)
        {

            std::shared_ptr<Expression> left_expression;
            try
            {
                auto left = this->visit(lvalue)
                                .as<Expression *>();
                left_expression = std::shared_ptr<Expression>(left);
            }
            catch (...)
            {
                _error_listener->Add(lvalue, "Error while parsing left value expression of a binary expression.");
            }

            std::shared_ptr<Expression> right_expression;
            try
            {
                auto right = this->visit(rvalue)
                                 .as<Expression *>();
                right_expression = std::shared_ptr<Expression>(right);
            }
            catch (...)
            {
                _error_listener->Add(rvalue, "Error while parsing right value expression of a binary expression");
            }

            std::shared_ptr<Operator> opr_expression;
            auto expr_operator = new Operator(opr->getText());
            if (INVALID_OPERATOR != expr_operator->GetOperatorType())
            {
                opr_expression = std::shared_ptr<Operator>(expr_operator);
            }

            Expression *expression = nullptr;
            if ((left_expression) && (opr) && (right_expression))
            {
                expression = new BinaryExpression(left_expression,
                                                  opr_expression,
                                                  right_expression);
            }
            return Any(expression);
        }
    } // namespace parser
} // namespace hoo