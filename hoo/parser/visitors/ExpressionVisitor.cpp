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

        Any ExpressionVisitor::visitByteConstant(HooParser::ByteConstantContext *ctx)
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

        Any ExpressionVisitor::visitBooleanConstant(HooParser::BooleanConstantContext *ctx)
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
            auto container = this->visit(ctx->container).as<Expression *>();
            auto accessIndex = this->visit(ctx->accessIndex).as<Expression *>();
            auto expression = (Expression *)new ArrayAccessExpression(container, accessIndex);
            return Any(expression);
        }

        Any ExpressionVisitor::visitExprInvoke(HooParser::ExprInvokeContext *ctx)
        {
            auto receiver = this->visit(ctx->receiver).as<Expression *>();
            std::list<Expression *> argumentList;
            if (nullptr != ctx->arguments)
            {
                auto arguments = ctx->arguments->expression();
                for (auto argument : arguments)
                {
                    auto expression = this->visit(argument).as<Expression *>();
                    argumentList.push_back(expression);
                }
            }

            Expression *expression = new InvokeExpression(receiver, argumentList);
            return Any(expression);
        }

        Any ExpressionVisitor::visitNestedRefExpr(HooParser::NestedRefExprContext *ctx)
        {
            auto parent = this->visit(ctx->parent).as<Expression *>();
            std::string name = "";
            if (nullptr != ctx->name)
            {
                name = ctx->name->getText();
            }

            regex reg_expr("([0-9A-Fa-f]+)(p|P)(\\d+)");

            if (parent->GetExpressionType() == EXPRESSION_LITERAL)
            {
                auto literal = (LiteralExpression *)parent;
                if (LITERAL_INTEGER == literal->GetLiteralType())
                {
                    cmatch match;
                    if (regex_match(name.c_str(), match, reg_expr))
                    {
                        std::string text = literal->GetValue();
                        text += ".";
                        text += name;
                        delete parent;
                        auto decimalExpression = (Expression *)new LiteralExpression(LITERAL_DOUBLE, text);
                        return Any(decimalExpression);
                    }
                }
            }

            auto expression = (Expression *)new ReferenceExpression(parent, name);
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

            auto left = this->visit(lvalue).as<Expression *>();
            auto right = this->visit(rvalue).as<Expression *>();
            auto oprText = new Operator(opr->getText());
            Expression *expr = new BinaryExpression(left, oprText, right);
            return expr;
        }
    } // namespace parser
} // namespace hoo