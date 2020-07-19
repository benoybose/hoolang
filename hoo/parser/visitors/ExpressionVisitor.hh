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

#ifndef EXPRESSION_VISITOR_HH
#define EXPRESSION_VISITOR_HH

#include "HooBaseVisitor.h"

#include <hoo/ast/AST.hh>
#include <hoo/parser/ErrorListener.hh>

using namespace antlr4;
using namespace antlrcpp;
using namespace hoo::ast;

namespace hoo
{
    namespace parser
    {
        class ExpressionVisitor : public HooBaseVisitor
        {
        private:
            ErrorListener *_error_listener;

        public:
            ExpressionVisitor(ErrorListener *error_listener);

        public:
            Any visitConstantByte(HooParser::ConstantByteContext *ctx) override;
            Any visitConstantInteger(HooParser::ConstantIntegerContext *ctx) override;
            Any visitConstantFloating(HooParser::ConstantFloatingContext *ctx) override;
            Any visitConstantCharacter(HooParser::ConstantCharacterContext *ctx) override;
            Any visitConstantBoolean(HooParser::ConstantBooleanContext *ctx) override;
            Any visitPrimaryConstantExpr(HooParser::PrimaryConstantExprContext *ctx) override;
            Any visitPrimaryStringExpr(HooParser::PrimaryStringExprContext *ctx) override;
            Any visitPrimaryRefExpr(HooParser::PrimaryRefExprContext *ctx) override;
            Any visitExprPrimary(HooParser::ExprPrimaryContext *ctx) override;
            Any visitArrayAccessExpr(HooParser::ArrayAccessExprContext *ctx) override;
            Any visitExprInvoke(HooParser::ExprInvokeContext *ctx) override;
            Any visitNestedRefExpr(HooParser::NestedRefExprContext *ctx) override;
            Any visitExprBitwise(HooParser::ExprBitwiseContext *ctx) override;
            Any visitExprAdditive(HooParser::ExprAdditiveContext *ctx) override;
            Any visitExprMultiplicative(HooParser::ExprMultiplicativeContext *ctx) override;
            Any visitExprComparison(HooParser::ExprComparisonContext *ctx) override;
            Any visitExprLogical(HooParser::ExprLogicalContext *ctx) override;
            Any visitExpAssignment(HooParser::ExpAssignmentContext *ctx) override;
            Any visitExprGrouped(HooParser::ExprGroupedContext *ctx) override;
            Expression *CreateBinaryExpression(HooParser::ExpressionContext *lvalue,
                                               antlr4::Token *opr,
                                               HooParser::ExpressionContext *rvalue,
                                               ParserRuleContext *context);
        };
    } // namespace parser
} // namespace hoo

#endif