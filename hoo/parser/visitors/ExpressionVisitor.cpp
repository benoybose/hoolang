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

        Any ExpressionVisitor::visitConstantByte(HooParser::ConstantByteContext *ctx)
        {
            auto value = ctx->getText();
            auto expression = new LiteralExpression(LITERAL_BYTE, value);
            return Any(expression);
        }

        Any ExpressionVisitor::visitConstantInteger(HooParser::ConstantIntegerContext *ctx)
        {
            auto value = ctx->getText();
            auto expression = new LiteralExpression(LITERAL_INTEGER, value);
            return Any(expression);
        }

        Any ExpressionVisitor::visitConstantFloating(HooParser::ConstantFloatingContext *ctx)
        {
            auto value = ctx->getText();
            auto expression = new LiteralExpression(LITERAL_DOUBLE, value);
            return Any(expression);
        }

        Any ExpressionVisitor::visitConstantCharacter(HooParser::ConstantCharacterContext *ctx)
        {
            auto value = ctx->getText();
            auto expression = new LiteralExpression(LITERAL_CHARACTER, value);
            return Any(expression);
        }

        Any ExpressionVisitor::visitConstantBoolean(HooParser::ConstantBooleanContext *ctx)
        {
            auto value = ctx->getText();
            if ((0 == value.compare("true")) ||
                (0 == value.compare("false")))
            {
                auto expression = new LiteralExpression(LITERAL_BOOLEAN, value);
                return Any(expression);
            }
            else
            {
                return Any(nullptr);
            }
        }

        Any ExpressionVisitor::visitPrimaryConstantExpr(
            HooParser::PrimaryConstantExprContext *ctx)
        {
            auto expression = (Expression *)this->visit(ctx->constant())
                                  .as<LiteralExpression *>();
            return Any(expression);
        }

        Any ExpressionVisitor::visitPrimaryStringExpr(HooParser::PrimaryStringExprContext *ctx)
        {
            auto text = ctx->StringLiteral()->getText();
            auto expression = (Expression *)new LiteralExpression(LITERAL_STRING, text);
            return Any(expression);
        }

        Any ExpressionVisitor::visitPrimaryRefExpr(HooParser::PrimaryRefExprContext *ctx)
        {
            auto name = ctx->Identifier()->getText();
            auto expression = (Expression *)new ReferenceExpression(name);
            return Any(expression);
        }

        Any ExpressionVisitor::visitExprPrimary(HooParser::ExprPrimaryContext *ctx)
        {
            auto expression = this->visit(ctx->primaryExpression()).as<Expression *>();
            return Any(expression);
        }

        Any ExpressionVisitor::visitArrayAccessExpr(HooParser::ArrayAccessExprContext *ctx)
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

        Any ExpressionVisitor::visitExprInvoke(HooParser::ExprInvokeContext *ctx)
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

        Any ExpressionVisitor::visitNestedRefExpr(HooParser::NestedRefExprContext *ctx)
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

            Expression* expression = new ReferenceExpression(parent, name);
            return Any(expression);
        }

        Any ExpressionVisitor::visitExprBitwise(HooParser::ExprBitwiseContext *ctx)
        {
            auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitExprAdditive(HooParser::ExprAdditiveContext *ctx)
        {
            auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitExprMultiplicative(HooParser::ExprMultiplicativeContext *ctx)
        {
            auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitExprComparison(HooParser::ExprComparisonContext *ctx)
        {
            auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitExprLogical(HooParser::ExprLogicalContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                                      ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitExpAssignment(HooParser::ExpAssignmentContext *ctx)
        {
            Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                                      ctx->opr, ctx->rvalue, ctx);
            return Any((Expression *)expr);
        }

        Any ExpressionVisitor::visitExprGrouped(HooParser::ExprGroupedContext *ctx)
        {
            auto expression = this->visit(ctx->expression()).as<Expression *>();
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