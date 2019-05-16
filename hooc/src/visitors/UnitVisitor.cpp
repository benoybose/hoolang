//
// Created by benoy on 5/16/2019.
//

#include "UnitVisitor.hh"

antlrcpp::Any UnitVisitor::visitUnit(HooParser::UnitContext *ctx) {
    return HooBaseVisitor::visitUnit(ctx);
}

antlrcpp::Any UnitVisitor::visitNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *ctx) {
    return HooBaseVisitor::visitNamespaceDeclaraion(ctx);
}

antlrcpp::Any UnitVisitor::visitUseSpecifier(HooParser::UseSpecifierContext *ctx) {
    return HooBaseVisitor::visitUseSpecifier(ctx);
}

antlrcpp::Any UnitVisitor::visitRootStatement(HooParser::RootStatementContext *ctx) {
    return HooBaseVisitor::visitRootStatement(ctx);
}
