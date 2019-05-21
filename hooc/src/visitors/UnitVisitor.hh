//
// Created by benoy on 5/16/2019.
//

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

};


#endif //PROJECT_UNITVISITOR_HH
