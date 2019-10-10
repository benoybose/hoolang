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


class UnitVisitor : public HooBaseVisitor {
public:

    antlrcpp::Any visitNamespaceDeclaration(HooParser::NamespaceDeclarationContext *ctx) override;

    antlrcpp::Any visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx) override;

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

    antlrcpp::Any visitExprPrimary(HooParser::ExprPrimaryContext *ctx) override;

    antlrcpp::Any visitExprBinary(HooParser::ExprBinaryContext *ctx) override;

    antlrcpp::Any visitExprGrouped(HooParser::ExprGroupedContext *ctx) override;

    antlrcpp::Any visitInvocationExpression(HooParser::InvocationExpressionContext *ctx) override;

    antlrcpp::Any visitCompoundStatement(HooParser::CompoundStatementContext *ctx) override;

    antlrcpp::Any visitReturnStatement(HooParser::ReturnStatementContext *ctx) override;

    antlrcpp::Any visitDeclarationStatement(HooParser::DeclarationStatementContext *ctx) override;

    antlrcpp::Any visitExpressionStatement(HooParser::ExpressionStatementContext *ctx) override;

    antlrcpp::Any visitUnit(HooParser::UnitContext *ctx) override;

    antlrcpp::Any visitClassDefinitionUnitItem(HooParser::ClassDefinitionUnitItemContext *ctx) override;

    antlrcpp::Any visitStatementUnitItem(HooParser::StatementUnitItemContext *ctx) override;

    antlrcpp::Any visitStmtNoop(HooParser::StmtNoopContext *ctx) override;

    antlrcpp::Any visitStmtCompound(HooParser::StmtCompoundContext *ctx) override;

    antlrcpp::Any visitStmtReturn(HooParser::StmtReturnContext *ctx) override;

    antlrcpp::Any visitStmtDeclaration(HooParser::StmtDeclarationContext *ctx) override;

    antlrcpp::Any visitStmtExpression(HooParser::StmtExpressionContext *ctx) override;

    antlrcpp::Any visitBooleanConstant(HooParser::BooleanConstantContext *ctx) override;

    antlrcpp::Any visitByteConstant(HooParser::ByteConstantContext *ctx) override;

    antlrcpp::Any visitExprLogical(HooParser::ExprLogicalContext *ctx) override;

};


#endif //PROJECT_UNITVISITOR_HH
