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

#include <iostream>
#include "HooLexer.h"
#include <hoo/parser/UnitVisitor.hh>
#include <hoo/ast/AST.hh>

#include <list>
#include <string>
#include <utility>
#include <regex>

using namespace hoo::ast;
using namespace antlrcpp;

UnitVisitor::UnitVisitor()
{
}

Any UnitVisitor::visitBasicDataTypeSpecifier(HooParser::BasicDataTypeSpecifierContext *ctx)
{
    auto basicDataType = GetBasicDataType(ctx->BasicDataType()->getText());
    if (BASIC_DATA_TYPE_INVALID == basicDataType)
    {
        // todo: Error handling
    }
    TypeSpecification *type = new BasicDataTypeSpecification(basicDataType);
    return Any(type);
}

Any UnitVisitor::visitNestedTypeSpecifier(HooParser::NestedTypeSpecifierContext *ctx)
{
    auto parent = this->visit(ctx->typeSpecifier())
                      .as<TypeSpecification *>();
    if (TYPE_SPEC_REFERENCE != parent->GetType())
    {
        // todo: Error handling
    }
    auto name = ctx->Identifier()->getText();
    TypeSpecification *type = new ReferenceDataTypeSpecification(name,
                                                                 (ReferenceDataTypeSpecification *)parent);
    return Any(type);
}

Any UnitVisitor::visitIdentifierTypeSpecifier(HooParser::IdentifierTypeSpecifierContext *ctx)
{
    auto name = ctx->Identifier()->getText();
    TypeSpecification *type = new ReferenceDataTypeSpecification(name, nullptr);
    return Any(type);
}

Any UnitVisitor::visitArrayTypeSpecifier(HooParser::ArrayTypeSpecifierContext *ctx)
{
    auto parent = this->visit(ctx->typeSpecifier())
                      .as<TypeSpecification *>();
    TypeSpecification *type = new ArrayDataTypeSpecification(parent);
    return Any(type);
}

Any UnitVisitor::visitMultipleItemParamList(HooParser::MultipleItemParamListContext *ctx)
{
    auto param_list = this->visit(ctx->list).as<std::list<VariableDeclaration *>>();
    auto declarations = ctx->variableDeclaration();
    for (auto declaration : declarations)
    {
        auto item = this->visit(declaration).as<VariableDeclaration *>();
        param_list.push_back(item);
    }
    return Any(param_list);
}

Any UnitVisitor::visitSingleItemParamList(HooParser::SingleItemParamListContext *ctx)
{
    auto declaration = this->visit(ctx->decl).as<VariableDeclaration *>();
    std::list<VariableDeclaration *> param_list;
    param_list.push_back(declaration);
    return Any(param_list);
}

Any UnitVisitor::visitPrimaryRefExpr(HooParser::PrimaryRefExprContext *ctx)
{
    auto name = ctx->Identifier()->getText();
    auto expression = (Expression *)new ReferenceExpression(name);
    return Any(expression);
}

Any UnitVisitor::visitNestedRefExpr(HooParser::NestedRefExprContext *ctx)
{
    auto parent = this->visit(ctx->parent).as<Expression *>();
    std::string name = "";
    if (nullptr != ctx->name)
    {
        name = ctx->name->getText();
    }

    regex reg_expr("([0-9A-Fa-f]+)(p|P)(\\d+)");

    if (parent->GetExpressionType() == EXPRESSION_LITERAL)
    {
        auto literal = (LiteralExpression *)parent;
        if (LITERAL_INTEGER == literal->GetLiteralType())
        {
            cmatch match;
            if (regex_match(name.c_str(), match, reg_expr))
            {
                std::string text = literal->GetValue();
                text += ".";
                text += name;
                delete parent;
                auto decimalExpression = (Expression *)new LiteralExpression(LITERAL_DOUBLE, text);
                return Any(decimalExpression);
            }
        }
    }

    auto expression = (Expression *)new ReferenceExpression(parent, name);
    return Any(expression);
}

Any UnitVisitor::visitPrimaryConstantExpr(HooParser::PrimaryConstantExprContext *ctx)
{
    auto expression = (Expression *)this->visit(ctx->constant()).as<LiteralExpression *>();
    return Any(expression);
}

Any UnitVisitor::visitPrimaryStringExpr(HooParser::PrimaryStringExprContext *ctx)
{
    auto text = ctx->StringLiteral()->getText();
    auto expression = (Expression *)new LiteralExpression(LITERAL_STRING, text);
    return Any(expression);
}

Any UnitVisitor::visitArrayAccessExpr(HooParser::ArrayAccessExprContext *ctx)
{
    auto container = this->visit(ctx->container).as<Expression *>();
    auto accessIndex = this->visit(ctx->accessIndex).as<Expression *>();
    auto expression = (Expression *)new ArrayAccessExpression(container, accessIndex);
    return Any(expression);
}

Any UnitVisitor::visitConstantInteger(HooParser::ConstantIntegerContext *ctx)
{
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_INTEGER, value);
    return Any(expression);
}

Any UnitVisitor::visitByteConstant(HooParser::ByteConstantContext *ctx)
{
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_BYTE, value);
    return Any(expression);
}

Any UnitVisitor::visitConstantFloating(HooParser::ConstantFloatingContext *ctx)
{
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_DOUBLE, value);
    return Any(expression);
}

Any UnitVisitor::visitConstantCharacter(HooParser::ConstantCharacterContext *ctx)
{
    auto value = ctx->getText();
    auto expression = new LiteralExpression(LITERAL_CHARACTER, value);
    return Any(expression);
}

Any UnitVisitor::visitBooleanConstant(HooParser::BooleanConstantContext *ctx)
{
    auto value = ctx->getText();
    if ((0 == value.compare("true")) ||
        (0 == value.compare("false")))
    {
        auto expression = new LiteralExpression(LITERAL_BOOLEAN, value);
        return Any(expression);
    }
    else
    {
        return Any(nullptr);
    }
}

Any UnitVisitor::visitExprInvoke(HooParser::ExprInvokeContext *ctx)
{
    auto receiver = this->visit(ctx->receiver).as<Expression *>();
    std::list<Expression *> argumentList;
    if (nullptr != ctx->arguments)
    {
        auto arguments = ctx->arguments->expression();
        for (auto argument : arguments)
        {
            auto expression = this->visit(argument).as<Expression *>();
            argumentList.push_back(expression);
        }
    }

    Expression *expression = new InvokeExpression(receiver, argumentList);
    return Any(expression);
}

Any UnitVisitor::visitExprPrimary(HooParser::ExprPrimaryContext *ctx)
{
    auto expression = this->visit(ctx->primaryExpression()).as<Expression *>();
    return Any(expression);
}

Any UnitVisitor::visitExprBitwise(HooParser::ExprBitwiseContext *ctx)
{
    auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
    return Any((Expression *)expr);
}

Any UnitVisitor::visitExprAdditive(HooParser::ExprAdditiveContext *ctx)
{
    auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
    return Any((Expression *)expr);
}

Any UnitVisitor::visitExprMultiplicative(HooParser::ExprMultiplicativeContext *ctx)
{
    auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
    return Any((Expression *)expr);
}

Any UnitVisitor::visitExprComparison(HooParser::ExprComparisonContext *ctx)
{
    auto expr = CreateBinaryExpression(ctx->lvalue, ctx->opr, ctx->rvalue, ctx);
    return Any((Expression *)expr);
}

Any UnitVisitor::visitExprLogical(HooParser::ExprLogicalContext *ctx)
{
    Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                              ctx->opr, ctx->rvalue, ctx);
    return Any((Expression *)expr);
}

Any UnitVisitor::visitExpAssignment(HooParser::ExpAssignmentContext *ctx)
{
    Expression *expr = CreateBinaryExpression(ctx->lvalue,
                                              ctx->opr, ctx->rvalue, ctx);
    return Any((Expression *)expr);
}

Any UnitVisitor::visitExprGrouped(HooParser::ExprGroupedContext *ctx)
{
    auto expression = this->visit(ctx->expression()).as<Expression *>();
    return Any(expression);
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

Any UnitVisitor::visitVariableDeclaration(HooParser::VariableDeclarationContext *ctx)
{
    DeclaratorType declaratorLabel = DECLARATOR_NONE;
    auto declarator = ctx->Declarator();
    if (nullptr != declarator)
    {
        declaratorLabel = this->GetDeclarator(ctx->Declarator()->getText());
    }

    auto name = ctx->name->getText();
    auto declared_type = this->visit(ctx->declared_type).as<TypeSpecification *>();
    Expression *initializer = nullptr;
    if (nullptr != ctx->init)
    {
        initializer = this->visit(ctx->init).as<Expression *>();
    }

    auto declaration = new VariableDeclaration(declaratorLabel, name,
                                               declared_type, initializer);
    return Any(declaration);
}

Any UnitVisitor::visitStmtFunctionDeclaration(HooParser::StmtFunctionDeclarationContext *ctx)
{
    auto declaration = this->visit(ctx->functionDeclaration())
                           .as<FunctionDeclaration *>();
    auto stmt = new DeclarationStatement(declaration);
    return Any(stmt);
}

Any UnitVisitor::visitFunctionDeclaration(HooParser::FunctionDeclarationContext *ctx)
{
    DeclaratorType declarator_type = DECLARATOR_NONE;
    auto declarator = ctx->Declarator();
    if (nullptr != declarator)
    {
        declarator_type = this->GetDeclarator(declarator->getText());
    }

    TypeSpecification *return_type = nullptr;
    if (nullptr != ctx->returnType)
    {
        return_type = this->visit(ctx->returnType).as<TypeSpecification *>();
    }

    std::string name = ctx->name->getText();
    auto parameterList = ctx->paramList();
    std::list<VariableDeclaration *> param_list;
    if (nullptr != parameterList)
    {
        param_list = this->visit(parameterList)
                         .as<std::list<VariableDeclaration *>>();
    }

    auto declaration = new FunctionDeclaration(declarator_type,
                                               return_type, name, param_list);
    return Any(declaration);
}

antlrcpp::Any UnitVisitor::visitFunctionDefinition(HooParser::FunctionDefinitionContext *ctx)
{
    auto declaration = this->visit(ctx->functionDeclaration())
                           .as<FunctionDeclaration *>();
    auto body = this->visit(ctx->operativeStatement())
                    .as<Statement *>();
    auto definition = (Definition *)new FunctionDefinition(declaration, body);
    return Any(definition);
}

Any UnitVisitor::visitDefinitionUnitItem(HooParser::DefinitionUnitItemContext *ctx)
{
    auto definition = this->visit(ctx->defenition())
                          .as<Definition *>();
    auto unit_item = (UnitItem *)definition;
    return Any(unit_item);
}

Any UnitVisitor::visitStatementUnitItem(HooParser::StatementUnitItemContext *ctx)
{
    auto statement = this->visit(ctx->statement()).as<Statement *>();
    auto unit_item = (UnitItem *)statement;
    return Any(unit_item);
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
    }

    auto unit = new Unit(unit_items);
    return Any(unit);
}

Any UnitVisitor::visitClassDefinition(HooParser::ClassDefinitionContext *ctx)
{
    auto className = ctx->className->getText();
    auto classDefinition = new ClassDefinition(className);
    Definition *definition = (Definition *) classDefinition;
    return Any(definition);
}

Expression *UnitVisitor::CreateBinaryExpression(HooParser::ExpressionContext *lvalue, antlr4::Token *opr,
                                                HooParser::ExpressionContext *rvalue, ParserRuleContext *context)
{
    auto left = this->visit(lvalue).as<Expression *>();
    auto right = this->visit(rvalue).as<Expression *>();
    auto oprText = new Operator(opr->getText());
    Expression *expr = new BinaryExpression(left, oprText, right);
    return expr;
}

DeclaratorType UnitVisitor::GetDeclarator(const std::string &declarator) const
{
    if (declarator.empty())
    {
        return DECLARATOR_NONE;
    }
    else if (declarator == "public")
    {
        return DECLARATOR_PUBLIC;
    }
    else if (declarator == "private")
    {
        return DECLARATOR_PRIVATE;
    }
    else if (declarator == "protected")
    {
        return DECLARATOR_PROTECTED;
    }
    else if (declarator == "var")
    {
        return DECLARATOR_VAR;
    }
    else
    {
        return DECLARATOR_INVALID;
    }
}
