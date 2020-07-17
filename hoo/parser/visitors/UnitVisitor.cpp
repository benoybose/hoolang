/*
 * Copyright 2020 Benoy Bose
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

#include <iostream>
#include "HooLexer.h"

#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/VisitorHelper.hh>
#include <hoo/parser/ErrorListener.hh>
#include <hoo/parser/visitors/UnitVisitor.hh>
#include <hoo/parser/visitors/DefinitionVisitor.hh>
#include <hoo/parser/visitors/StatementVisitor.hh>

#include <list>
#include <string>
#include <utility>
#include <regex>
#include <memory>

using namespace hoo::ast;
using namespace antlrcpp;
using namespace hoo::parser;

UnitVisitor::UnitVisitor(ErrorListener *error_listener)
    : _error_listener(error_listener)
{
}

Any UnitVisitor::visitCompoundStatement(HooParser::CompoundStatementContext *ctx)
{
    auto statements = ctx->statement();
    std::list<Statement *> statement_list;
    for (auto statement_ctx : statements)
    {
        auto statement = this->visit(statement_ctx).as<Statement *>();
        statement_list.push_back(statement);
    }
    auto compoundStatement = new CompoundStatement(statement_list);
    return Any(compoundStatement);
}

Any UnitVisitor::visitReturnStatement(HooParser::ReturnStatementContext *ctx)
{
    if (nullptr == ctx->returnValue)
    {
        return Any(new ReturnStatement());
    }
    else
    {
        auto expression = this->visit(ctx->returnValue).as<Expression *>();
        auto statement = new ReturnStatement(expression);
        return Any(statement);
    }
}

Any UnitVisitor::visitExpressionStatement(HooParser::ExpressionStatementContext *ctx)
{
    auto expression = this->visit(ctx->expression()).as<Expression *>();
    auto expressionStatement = new ExpressionStatement(expression);
    return Any(expressionStatement);
}

Any UnitVisitor::visitStmtNoop(HooParser::StmtNoopContext *ctx)
{
    auto noop_statement = new NoopStatement();
    auto stmt = (Statement *)noop_statement;
    return Any(stmt);
}

Any UnitVisitor::visitStmtCompound(HooParser::StmtCompoundContext *ctx)
{
    auto compound_statement = this->visit(ctx->compoundStatement()).as<CompoundStatement *>();
    auto stmt = (Statement *)compound_statement;
    return Any(stmt);
}

Any UnitVisitor::visitStmtReturn(HooParser::StmtReturnContext *ctx)
{
    auto return_statement = this->visit(ctx->returnStatement()).as<ReturnStatement *>();
    auto stmt = (Statement *)return_statement;
    return Any(stmt);
}

Any UnitVisitor::visitStmtDeclaration(HooParser::StmtDeclarationContext *ctx)
{
    auto declaration_statement = this->visit(ctx->declarationStatement()).as<DeclarationStatement *>();
    auto stmt = (Statement *)declaration_statement;
    return Any(stmt);
}

Any UnitVisitor::visitStmtExpression(HooParser::StmtExpressionContext *ctx)
{
    auto expression_statement = this->visit(ctx->expressionStatement()).as<ExpressionStatement *>();
    auto stmt = (Statement *)expression_statement;
    return Any(stmt);
}

Any UnitVisitor::visitStmtOperative(HooParser::StmtOperativeContext *ctx)
{
    auto statement = this->visit(ctx->operativeStatement())
                         .as<Statement *>();
    return Any(statement);
}

Any UnitVisitor::visitStmtVariableDeclaration(HooParser::StmtVariableDeclarationContext *ctx)
{
    auto variableDeclaration = this->visit(ctx->variableDeclaration())
                                   .as<VariableDeclaration *>();
    auto stmt = new DeclarationStatement(variableDeclaration);
    return Any(stmt);
}

Any UnitVisitor::visitStmtFunctionDeclaration(HooParser::StmtFunctionDeclarationContext *ctx)
{
    auto declaration = this->visit(ctx->functionDeclaration())
                           .as<FunctionDeclaration *>();
    auto stmt = new DeclarationStatement(declaration);
    return Any(stmt);
}

Any UnitVisitor::visitUnit(HooParser::UnitContext *ctx)
{
    auto items = ctx->unitItem();
    UnitItemList unit_items;
    for (auto item : items)
    {
        auto unit_item = this->visit(item).as<UnitItem *>();
        if (nullptr != unit_item)
        {
            unit_items.push_back(std::shared_ptr<UnitItem>(unit_item));
        }
        else
        {
            _error_listener->Add(item, "Invalid source.");
        }
    }

    auto unit = new Unit(unit_items);
    return Any(unit);
}

Any UnitVisitor::visitUnitItem(HooParser::UnitItemContext *ctx)
{
    auto definition_context = ctx->defenition();
    UnitItem *unit_item = nullptr;

    if (nullptr != definition_context)
    {
        DefinitionVisitor visitor(_error_listener);
        auto definition = visitor.visit(definition_context).as<Definition *>();
        unit_item = (UnitItem *)definition;
    }
    else
    {
        auto statement_context = ctx->statement();
        if (nullptr != statement_context)
        {
            StatementVisitor visitor(_error_listener);
            auto statement = visitor.visit(statement_context).as<Statement *>();
            unit_item = (UnitItem *)statement;
        }
    }

    return Any(unit_item);
}
