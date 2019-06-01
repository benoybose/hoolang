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

#include "HooLexer.h"
#include "UnitVisitor.hh"
#include "ast/TypeSpecification.hh"
#include "ast/Declaration.hh"
#include "ast/FunctionDefinition.hh"
#include "ast/ReferenceExpression.hh"
#include "ast/LiteralExpression.hh"
#include "ast/BinaryExpression.hh"
#include "ast/ArrayAccessExpression.hh"
#include "ast/InvokeExpression.h"
#include "ast/Statement.hh"

#include <list>
#include <string>

using namespace hooc::ast;
using namespace antlrcpp;

Any UnitVisitor::visitNamespaceDeclaration(HooParser::NamespaceDeclarationContext *ctx) {
    auto identifiers = ctx->Identifier();
    std::list<std::string> namespace_items;
    for (auto identifier : identifiers) {
        auto namespace_item = identifier->getText();
        namespace_items.push_back(namespace_item);
    }
    return antlrcpp::Any(namespace_items);
}



Any UnitVisitor::visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx) {

    auto declarator = ctx->Declarator()->getText();
    TypeSpecification *return_type = nullptr;
    if (nullptr != ctx->returnType) {
        return_type = this->visit(ctx->returnType).as<TypeSpecification *>();
    }
    std::string function_name = ctx->name->getText();
    std::list<Declaration*> param_list;
    if(nullptr != ctx->paramList()) {
        param_list = this->visit(ctx->paramList()).as<std::list<Declaration*>>();
    }
    auto statement = this->visit(ctx->compoundStatement()).as<CompoundStatement*>();
    auto function_definition = new FunctionDefinition(declarator, function_name,
                                                      return_type,
                                                      param_list,
                                                      statement);
    return Any(function_definition);
}

Any UnitVisitor::visitDeclaration(HooParser::DeclarationContext *ctx) {
    auto name = ctx->name->getText();
    auto declared_type = this->visit(ctx->declared_type).as<TypeSpecification *>();
    auto initializer = this->visit(ctx->init->expression()).as<Expression*>();
    auto declaration = new Declaration(name, declared_type, initializer);
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

Any UnitVisitor::visitPrimaryRefExpr(HooParser::PrimaryRefExprContext *ctx) {
    auto name = ctx->Identifier()->getText();
    auto expression = new ReferenceExpression(name);
    return Any(expression);
}

Any UnitVisitor::visitPrimaryNestedRefExpr(HooParser::PrimaryNestedRefExprContext *ctx) {
    auto parent = this->visit(ctx->parent).as<ReferenceExpression*>();
    auto name = ctx->name->getText();
    auto expression = new ReferenceExpression(parent, name);
    return Any(expression);
}

Any UnitVisitor::visitPrimaryConstantExpr(HooParser::PrimaryConstantExprContext *ctx) {
    auto expression = this->visit(ctx->constant());
    return Any(expression);
}

Any UnitVisitor::visitPrimaryStringExpr(HooParser::PrimaryStringExprContext *ctx) {
    auto text = ctx->StringLiteral()->getText();
    auto expression = new LiteralExpression(LITERAL_STRING, text);
    return Any(expression);
}

Any UnitVisitor::visitPrimaryArrayAccessExpr(HooParser::PrimaryArrayAccessExprContext *ctx) {
    auto container = this->visit(ctx->container).as<Expression*>();
    auto accessIndex = this->visit(ctx->accessIndex).as<Expression*>();
    auto expression = new ArrayAccessExpression(container, accessIndex);
    return Any(expression);
}

Any UnitVisitor::visitConstantInteger(HooParser::ConstantIntegerContext *ctx) {
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_INTEGER, value);
    return Any(expression);
}

Any UnitVisitor::visitConstantFloating(HooParser::ConstantFloatingContext *ctx) {
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_DOUBLE, value);
    return Any(expression);
}

Any UnitVisitor::visitConstantCharacter(HooParser::ConstantCharacterContext *ctx) {
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_CHARACTER, value);
    return Any(expression);
}

Any UnitVisitor::visitExprInvoke(HooParser::ExprInvokeContext *ctx) {
    auto expression = this->visit(ctx->invokeExpression()).as<Expression*>();
    return Any(expression);
}

Any UnitVisitor::visitExprBinary(HooParser::ExprBinaryContext *ctx) {
    auto lvalue = this->visit(ctx->lvalue).as<Expression*>();
    auto opr = new Operator(ctx->opr->getText());
    auto rvalue = this->visit(ctx->rvalue).as<Expression*>();

    auto binaryExpresion = new BinaryExpression(lvalue, opr, rvalue);
    return Any(binaryExpresion);
}

Any UnitVisitor::visitExprGrouped(HooParser::ExprGroupedContext *ctx) {
    auto expression = this->visit(ctx->expression()).as<Expression*>();
    return Any(expression);
}

Any UnitVisitor::visitExprPrimary(HooParser::ExprPrimaryContext *ctx) {
    auto primaryExpression = this->visit(ctx->primaryExpression()).as<Expression*>();
    return Any(primaryExpression);
}

Any UnitVisitor::visitInvokeExpression(HooParser::InvokeExpressionContext *ctx) {
    auto receiver = this->visit(ctx->receiver).as<Expression*>();
    std::list<Expression*> argumentList;
    if(nullptr != ctx->arguments) {
        auto arguments = ctx->arguments->expression();
        for(auto argument: arguments) {
            auto expression = this->visit(argument).as<Expression*>();
            argumentList.push_back(expression);
        }
    }
    auto invokeExpression = new InvokeExpression(receiver, argumentList);
    return Any(invokeExpression);
}

Any UnitVisitor::visitReturnStatement(HooParser::ReturnStatementContext *ctx) {
    auto expression = this->visit(ctx->returnValue).as<Expression*>();
    auto statement = new ReturnStatement(expression);
    return Any(statement);
}

Any UnitVisitor::visitCompoundStatement(HooParser::CompoundStatementContext *ctx) {
    auto statements = ctx->statement();
    std::list<Statement*> statement_list;
    for(auto statement_ctx: statements) {
        auto statement = this->visit(statement_ctx).as<Statement*>();
        statement_list.push_back(statement);
    }
    auto compoundStatement = new CompoundStatement(statement_list);
    return Any(compoundStatement);
}

Any UnitVisitor::visitAssignmentStatement(HooParser::AssignmentStatementContext *ctx) {
    auto primary = this->visit(ctx->primary).as<Expression*>();
    auto value = this->visit(ctx->value).as<Expression*>();
    auto statement = new AssignmentStatement(primary, value);
    return Any(statement);
}

Any UnitVisitor::visitInvokeStatement(HooParser::InvokeStatementContext *ctx) {
    auto expression = this->visit(ctx->invokeExpression()).as<InvokeExpression*>();
    auto statement = new InvokeStatement(expression);
    return Any(statement);
}
