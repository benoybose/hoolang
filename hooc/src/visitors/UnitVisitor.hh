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
#include "ast/Expression.hh"
#include "ast/Operator.hh"
#include "ast/Declarator.hh"

using namespace hooc::ast;

class UnitVisitor : public HooBaseVisitor {
public:
    antlrcpp::Any visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx) override;

    antlrcpp::Any visitVariableDeclaration(HooParser::VariableDeclarationContext *ctx) override;

    antlrcpp::Any visitMultipleItemParamList(HooParser::MultipleItemParamListContext *ctx) override;

    antlrcpp::Any visitSingleItemParamList(HooParser::SingleItemParamListContext *ctx) override;

    antlrcpp::Any visitPrimaryRefExpr(HooParser::PrimaryRefExprContext *ctx) override;

    antlrcpp::Any visitNestedRefExpr(HooParser::NestedRefExprContext *ctx) override;

    antlrcpp::Any visitPrimaryConstantExpr(HooParser::PrimaryConstantExprContext *ctx) override;

    antlrcpp::Any visitPrimaryStringExpr(HooParser::PrimaryStringExprContext *ctx) override;

    antlrcpp::Any visitArrayAccessExpr(HooParser::ArrayAccessExprContext *ctx) override;

    antlrcpp::Any visitConstantInteger(HooParser::ConstantIntegerContext *ctx) override;

    antlrcpp::Any visitConstantFloating(HooParser::ConstantFloatingContext *ctx) override;

    antlrcpp::Any visitConstantCharacter(HooParser::ConstantCharacterContext *ctx) override;

    antlrcpp::Any visitExprInvoke(HooParser::ExprInvokeContext *ctx) override;

    antlrcpp::Any visitExprPrimary(HooParser::ExprPrimaryContext *ctx) override;

    antlrcpp::Any visitExprGrouped(HooParser::ExprGroupedContext *ctx) override;

    antlrcpp::Any visitCompoundStatement(HooParser::CompoundStatementContext *ctx) override;

    antlrcpp::Any visitReturnStatement(HooParser::ReturnStatementContext *ctx) override;

    antlrcpp::Any visitExpressionStatement(HooParser::ExpressionStatementContext *ctx) override;

    antlrcpp::Any visitUnit(HooParser::UnitContext *ctx) override;

    antlrcpp::Any visitStatementUnitItem(HooParser::StatementUnitItemContext *ctx) override;

    antlrcpp::Any visitStmtNoop(HooParser::StmtNoopContext *ctx) override;

    antlrcpp::Any visitStmtCompound(HooParser::StmtCompoundContext *ctx) override;

    antlrcpp::Any visitStmtReturn(HooParser::StmtReturnContext *ctx) override;

    antlrcpp::Any visitStmtDeclaration(HooParser::StmtDeclarationContext *ctx) override;

    antlrcpp::Any visitStmtExpression(HooParser::StmtExpressionContext *ctx) override;

    antlrcpp::Any visitBooleanConstant(HooParser::BooleanConstantContext *ctx) override;

    antlrcpp::Any visitByteConstant(HooParser::ByteConstantContext *ctx) override;

    antlrcpp::Any visitExprLogical(HooParser::ExprLogicalContext *ctx) override;

    antlrcpp::Any visitExprAdditive(HooParser::ExprAdditiveContext *ctx) override;

    antlrcpp::Any visitExprMultiplicative(HooParser::ExprMultiplicativeContext *ctx) override;

    antlrcpp::Any visitExprComparison(HooParser::ExprComparisonContext *ctx) override;

    antlrcpp::Any visitExpAssignment(HooParser::ExpAssignmentContext *ctx) override;

    antlrcpp::Any visitExprBitwise(HooParser::ExprBitwiseContext *ctx) override;

    antlrcpp::Any visitFunctionDeclaration(HooParser::FunctionDeclarationContext *ctx) override;

    antlrcpp::Any visitStmtVariableDeclaration(HooParser::StmtVariableDeclarationContext *ctx) override;

    antlrcpp::Any visitStmtFunctionDeclaration(HooParser::StmtFunctionDeclarationContext *ctx) override;

    antlrcpp::Any visitBasicDataTypeSpecifier(HooParser::BasicDataTypeSpecifierContext *ctx) override;

    antlrcpp::Any visitNestedTypeSpecifier(HooParser::NestedTypeSpecifierContext *ctx) override;

    antlrcpp::Any visitIdentifierTypeSpecifier(HooParser::IdentifierTypeSpecifierContext *ctx) override;

    antlrcpp::Any visitArrayTypeSpecifier(HooParser::ArrayTypeSpecifierContext *ctx) override;

    antlrcpp::Any visitDefinitionUnitItem(HooParser::DefinitionUnitItemContext *ctx) override;

private:

    Expression *CreateBinaryExpression(HooParser::ExpressionContext *lvalue,
                                       antlr4::Token *opr, HooParser::ExpressionContext *rvalue);

    DeclaratorType GetDeclarator(const std::string& declarator) const;

};


#endif //PROJECT_UNITVISITOR_HH
