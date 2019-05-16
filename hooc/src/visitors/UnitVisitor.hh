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
};


#endif //PROJECT_UNITVISITOR_HH
