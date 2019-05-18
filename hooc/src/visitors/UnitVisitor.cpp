//
// Created by benoy on 5/16/2019.
//

#include "UnitVisitor.hh"

#include <list>
#include <string>
#include <ast/TypeSpecification.hh>

using namespace hooc::ast;
using namespace antlrcpp;

Any UnitVisitor::visitUnit(HooParser::UnitContext *ctx) {
    std::list<std::string> unit_namespace;
    if (nullptr == ctx->namespaceDeclaration()) {
        unit_namespace = this->visit(ctx->namespaceDeclaration())
                .as<std::list<std::string>>();
    }

    //todo: Process use blocks
    return HooBaseVisitor::visitUnit(ctx);
}

Any UnitVisitor::visitNamespaceDeclaration(HooParser::NamespaceDeclarationContext *ctx) {
    auto identifiers = ctx->Identifier();
    std::list<std::string> namespace_items;
    for (auto identifier : identifiers) {
        auto namespace_item = identifier->getText();
        namespace_items.push_back(namespace_item);
    }
    return antlrcpp::Any(namespace_items);
}

Any UnitVisitor::visitUseSpecifier(HooParser::UseSpecifierContext *ctx) {
    return HooBaseVisitor::visitUseSpecifier(ctx);
}

Any UnitVisitor::visitRootStatement(HooParser::RootStatementContext *ctx) {
    if(nullptr != ctx->classDefinition()) {
        this->visit(ctx->classDefinition());
    }
    return HooBaseVisitor::visitRootStatement(ctx);
}

Any UnitVisitor::visitParamList(HooParser::ParamListContext *ctx) {
    return HooBaseVisitor::visitParamList(ctx);
}

Any UnitVisitor::visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx) {
    auto returnType = this->visit(ctx->returnType)
            .as<TypeSpecification*>();
    return HooBaseVisitor::visitFunctionDefinition(ctx);
}

Any UnitVisitor::visitClassDefinition(HooParser::ClassDefinitionContext *ctx) {
    return HooBaseVisitor::visitClassDefinition(ctx);
}

Any UnitVisitor::visitClassBody(HooParser::ClassBodyContext *ctx) {
    return HooBaseVisitor::visitClassBody(ctx);
}

Any UnitVisitor::visitClassBodyItem(HooParser::ClassBodyItemContext *ctx) {
    return HooBaseVisitor::visitClassBodyItem(ctx);
}

Any UnitVisitor::visitMethod(HooParser::MethodContext *ctx) {
    return HooBaseVisitor::visitMethod(ctx);
}

Any UnitVisitor::visitField(HooParser::FieldContext *ctx) {
    return HooBaseVisitor::visitField(ctx);
}

Any UnitVisitor::visitDeclaration(HooParser::DeclarationContext *ctx) {
    return HooBaseVisitor::visitDeclaration(ctx);
}

Any UnitVisitor::visitTypeSpecifier(HooParser::TypeSpecifierContext *ctx) {
    if(nullptr != ctx->Identifier()) {
        auto name = ctx->Identifier()->getText();
        if(nullptr != ctx->typeSpecifier()) {
            auto parent = this->visit(ctx->typeSpecifier()).as<TypeSpecification*>();
            auto type = new NestedTypeSpecification(parent, name);
            return Any(type);
        } else {
            auto type = new TypeSpecification(name);
            return Any(type);
        }
    } else if(nullptr != ctx->typeSpecifier()) {
        auto refer = this->visit(ctx->typeSpecifier()).as<TypeSpecification*>();
        auto type = new ArrayTypeSpecification(refer);
        return Any(type);
    } else {
        return Any(nullptr);
    }
}

