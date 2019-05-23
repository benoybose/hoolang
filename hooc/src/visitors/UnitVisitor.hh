/*
 * Copyright 2019 Benoy Bose
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

#ifndef PROJECT_UNITVISITOR_HH
#define PROJECT_UNITVISITOR_HH

#include "HooBaseVisitor.h"


class UnitVisitor: public HooBaseVisitor  {
public:
    antlrcpp::Any visitUnit(HooParser::UnitContext *ctx) override;

    antlrcpp::Any visitNamespaceDeclaration(HooParser::NamespaceDeclarationContext *ctx) override;

    antlrcpp::Any visitUseSpecifier(HooParser::UseSpecifierContext *ctx) override;

    antlrcpp::Any visitRootStatement(HooParser::RootStatementContext *ctx) override;

    antlrcpp::Any visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx) override;

    antlrcpp::Any visitClassDefinition(HooParser::ClassDefinitionContext *ctx) override;

    antlrcpp::Any visitClassBody(HooParser::ClassBodyContext *ctx) override;

    antlrcpp::Any visitClassBodyItem(HooParser::ClassBodyItemContext *ctx) override;

    antlrcpp::Any visitMethod(HooParser::MethodContext *ctx) override;

    antlrcpp::Any visitField(HooParser::FieldContext *ctx) override;

    antlrcpp::Any visitDeclaration(HooParser::DeclarationContext *ctx) override;

    antlrcpp::Any visitTypeSpecifier(HooParser::TypeSpecifierContext *ctx) override;

    antlrcpp::Any visitMultipleItemParamList(HooParser::MultipleItemParamListContext *ctx) override;

    antlrcpp::Any visitSingleItemParamList(HooParser::SingleItemParamListContext *ctx) override;

    antlrcpp::Any visitPrimaryRefExpr(HooParser::PrimaryRefExprContext *ctx) override;

    antlrcpp::Any visitPrimaryNestedRefExpr(HooParser::PrimaryNestedRefExprContext *ctx) override;

    antlrcpp::Any visitPrimaryConstantExpr(HooParser::PrimaryConstantExprContext *ctx) override;

    antlrcpp::Any visitPrimaryStringExpr(HooParser::PrimaryStringExprContext *ctx) override;

    antlrcpp::Any visitPrimaryArrayAccessExpr(HooParser::PrimaryArrayAccessExprContext *ctx) override;

    antlrcpp::Any visitConstantInteger(HooParser::ConstantIntegerContext *ctx) override;

    antlrcpp::Any visitConstantFloating(HooParser::ConstantFloatingContext *ctx) override;

    antlrcpp::Any visitConstantCharacter(HooParser::ConstantCharacterContext *ctx) override;

    antlrcpp::Any visitExprInvoke(HooParser::ExprInvokeContext *ctx) override;

    antlrcpp::Any visitExprBinary(HooParser::ExprBinaryContext *ctx) override;

    antlrcpp::Any visitExprGrouped(HooParser::ExprGroupedContext *ctx) override;

    antlrcpp::Any visitExprPrimary(HooParser::ExprPrimaryContext *ctx) override;

    antlrcpp::Any visitInvokeExpression(HooParser::InvokeExpressionContext *ctx) override;

};


#endif //PROJECT_UNITVISITOR_HH
