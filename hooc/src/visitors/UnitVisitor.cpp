//
// Created by benoy on 5/16/2019.
//

#include "UnitVisitor.hh"
#include "ast/TypeSpecification.hh"
#include "ast/Declaration.hh"
#include "ast/FunctionDefinition.hh"

#include <list>
#include <string>

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
    // todo" Construct use block
    return HooBaseVisitor::visitUseSpecifier(ctx);
}

Any UnitVisitor::visitRootStatement(HooParser::RootStatementContext *ctx) {
    if (nullptr != ctx->classDefinition()) {
        this->visit(ctx->classDefinition());
    }
    return HooBaseVisitor::visitRootStatement(ctx);
}

Any UnitVisitor::visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx) {
    TypeSpecification *return_type = nullptr;
    if (nullptr != ctx->returnType) {
        return_type = this->visit(ctx->returnType).as<TypeSpecification *>();
    }
    std::string function_name = ctx->name->getText();
    std::list<Declaration*> param_list;
    if(nullptr != ctx->paramList()) {
        param_list = this->visit(ctx->paramList()).as<std::list<Declaration*>>();
    }
    auto statement = ctx->statement();
    auto function_definition = new FunctionDefinition(function_name,
            return_type,
            param_list,
            statement);
    return Any(function_definition);
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
    auto name = ctx->name->getText();
    auto declared_type = this->visit(ctx->declared_type).as<TypeSpecification *>();
    auto initialiser = this->visit(ctx->init);
    auto declaration = new Declaration(name, declared_type, initialiser);
    return declaration;
}

Any UnitVisitor::visitTypeSpecifier(HooParser::TypeSpecifierContext *ctx) {
    if (nullptr != ctx->Identifier()) {
        auto name = ctx->Identifier()->getText();
        if (nullptr != ctx->typeSpecifier()) {
            auto parent = this->visit(ctx->typeSpecifier()).as<TypeSpecification *>();
            auto type = new NestedTypeSpecification(parent, name);
            return Any(type);
        } else {
            auto type = new TypeSpecification(name);
            return Any(type);
        }
    } else if (nullptr != ctx->typeSpecifier()) {
        auto refer = this->visit(ctx->typeSpecifier()).as<TypeSpecification *>();
        auto type = new ArrayTypeSpecification(refer);
        return Any(type);
    } else {
        return Any(nullptr);
    }
}

Any UnitVisitor::visitMultipleItemParamList(HooParser::MultipleItemParamListContext *ctx) {
    auto param_list = this->visit(ctx->paramList()).as<std::list<Declaration *>>();
    auto declarations = ctx->declaration();
    for(auto declaration: declarations) {
        auto item = this->visit(declaration).as<Declaration *>();
        param_list.push_back(item);
    }
    return Any(param_list);
}

Any UnitVisitor::visitSingleItemParamList(HooParser::SingleItemParamListContext *ctx) {
    auto declaration = this->visit(ctx->declaration()).as<Declaration*>();
    std::list<Declaration*> param_list;
    param_list.push_back(declaration);
    return Any(param_list);
}

