//
// Created by benoy on 5/16/2019.
//

#include "UnitVisitor.hh"

#include <list>
#include <string>

antlrcpp::Any UnitVisitor::visitUnit(HooParser::UnitContext *ctx) {
    std::list<std::string> unit_namespace;
    if (nullptr == ctx->namespaceDeclaraion()) {
        unit_namespace = this->visit(ctx->namespaceDeclaraion())
                .as<std::list<std::string>>();
    }

    //todo: Process use blocks
    return HooBaseVisitor::visitUnit(ctx);
}

antlrcpp::Any UnitVisitor::visitNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *ctx) {
    auto identifiers = ctx->Identifier();
    std::list<std::string> namespace_items;
    for (auto iterator = identifiers.begin();
         iterator != identifiers.end(); ++iterator) {
        auto identifier = *(iterator);
        auto namespace_item = identifier->getText();
        namespace_items.push_back(namespace_item);
    }
    return antlrcpp::Any(namespace_items);
}

antlrcpp::Any UnitVisitor::visitUseSpecifier(HooParser::UseSpecifierContext *ctx) {
    return HooBaseVisitor::visitUseSpecifier(ctx);
}

antlrcpp::Any UnitVisitor::visitRootStatement(HooParser::RootStatementContext *ctx) {
    if(nullptr != ctx->classDefinition()) {
        this->visit(ctx->classDefinition());
    }
    return HooBaseVisitor::visitRootStatement(ctx);
}

antlrcpp::Any UnitVisitor::visitParamList(HooParser::ParamListContext *ctx) {
    return HooBaseVisitor::visitParamList(ctx);
}

antlrcpp::Any UnitVisitor::visitFunctionDefintion(HooParser::FunctionDefintionContext *ctx) {
    return HooBaseVisitor::visitFunctionDefintion(ctx);
}

antlrcpp::Any UnitVisitor::visitClassDefinition(HooParser::ClassDefinitionContext *ctx) {
    return HooBaseVisitor::visitClassDefinition(ctx);
}

antlrcpp::Any UnitVisitor::visitClassBody(HooParser::ClassBodyContext *ctx) {
    return HooBaseVisitor::visitClassBody(ctx);
}

antlrcpp::Any UnitVisitor::visitClassBodyItem(HooParser::ClassBodyItemContext *ctx) {
    return HooBaseVisitor::visitClassBodyItem(ctx);
}

antlrcpp::Any UnitVisitor::visitMethod(HooParser::MethodContext *ctx) {
    return HooBaseVisitor::visitMethod(ctx);
}

antlrcpp::Any UnitVisitor::visitField(HooParser::FieldContext *ctx) {
    return HooBaseVisitor::visitField(ctx);
}
