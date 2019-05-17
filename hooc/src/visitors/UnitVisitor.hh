//
// Created by benoy on 5/16/2019.
//

#ifndef PROJECT_UNITVISITOR_HH
#define PROJECT_UNITVISITOR_HH

#include "HooBaseVisitor.h"


class UnitVisitor: public HooBaseVisitor  {
public:
    antlrcpp::Any visitUnit(HooParser::UnitContext *ctx) override;

    antlrcpp::Any visitNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *ctx) override;

    antlrcpp::Any visitUseSpecifier(HooParser::UseSpecifierContext *ctx) override;

    antlrcpp::Any visitRootStatement(HooParser::RootStatementContext *ctx) override;

    antlrcpp::Any visitParamList(HooParser::ParamListContext *ctx) override;

    antlrcpp::Any visitFunctionDefintion(HooParser::FunctionDefintionContext *ctx) override;

    antlrcpp::Any visitClassDefinition(HooParser::ClassDefinitionContext *ctx) override;

    antlrcpp::Any visitClassBody(HooParser::ClassBodyContext *ctx) override;

    antlrcpp::Any visitClassBodyItem(HooParser::ClassBodyItemContext *ctx) override;

    antlrcpp::Any visitMethod(HooParser::MethodContext *ctx) override;

    antlrcpp::Any visitField(HooParser::FieldContext *ctx) override;
};


#endif //PROJECT_UNITVISITOR_HH
