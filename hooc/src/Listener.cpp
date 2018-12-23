/*
 * Copyright 2018 Benoy Bose
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

#include <Listener.hh>

#include "Listener.hh"

namespace hooc
{
    Listener::Listener() {

    }

    void Listener::enterPrimaryExpression(HooParser::PrimaryExpressionContext *context) {
        HooBaseListener::enterPrimaryExpression(context);
    }

    void Listener::exitPrimaryExpression(HooParser::PrimaryExpressionContext *context) {
        HooBaseListener::exitPrimaryExpression(context);
    }

    void Listener::enterExpression(HooParser::ExpressionContext *context) {
        HooBaseListener::enterExpression(context);
    }

    void Listener::exitExpression(HooParser::ExpressionContext *context) {
        HooBaseListener::exitExpression(context);
    }

    void Listener::enterBinaryOperator(HooParser::BinaryOperatorContext *context) {
        HooBaseListener::enterBinaryOperator(context);
    }

    void Listener::exitBinaryOperator(HooParser::BinaryOperatorContext *context) {
        HooBaseListener::exitBinaryOperator(context);
    }

    void Listener::enterArithmeticOperator(HooParser::ArithmeticOperatorContext *context) {
        HooBaseListener::enterArithmeticOperator(context);
    }

    void Listener::exitArithmeticOperator(HooParser::ArithmeticOperatorContext *context) {
        HooBaseListener::exitArithmeticOperator(context);
    }

    void Listener::enterRelationalOperator(HooParser::RelationalOperatorContext *context) {
        HooBaseListener::enterRelationalOperator(context);
    }

    void Listener::exitRelationalOperator(HooParser::RelationalOperatorContext *context) {
        HooBaseListener::exitRelationalOperator(context);
    }

    void Listener::enterAssignmentOperator(HooParser::AssignmentOperatorContext *context) {
        HooBaseListener::enterAssignmentOperator(context);
    }

    void Listener::exitAssignmentOperator(HooParser::AssignmentOperatorContext *context) {
        HooBaseListener::exitAssignmentOperator(context);
    }

    void Listener::enterTypeSepecifier(HooParser::TypeSepecifierContext *context) {
        HooBaseListener::enterTypeSepecifier(context);
    }

    void Listener::exitTypeSepecifier(HooParser::TypeSepecifierContext *context) {
        HooBaseListener::exitTypeSepecifier(context);
    }

    void Listener::enterDeclaration(HooParser::DeclarationContext *context) {
        HooBaseListener::enterDeclaration(context);
    }

    void Listener::exitDeclaration(HooParser::DeclarationContext *context) {
        HooBaseListener::exitDeclaration(context);
    }

    void Listener::enterParamList(HooParser::ParamListContext *context) {
        HooBaseListener::enterParamList(context);
    }

    void Listener::exitParamList(HooParser::ParamListContext *context) {
        HooBaseListener::exitParamList(context);
    }

    void Listener::enterInitializer(HooParser::InitializerContext *context) {
        HooBaseListener::enterInitializer(context);
    }

    void Listener::exitInitializer(HooParser::InitializerContext *context) {
        HooBaseListener::exitInitializer(context);
    }

    void Listener::enterInvokeExpression(HooParser::InvokeExpressionContext *context) {
        HooBaseListener::enterInvokeExpression(context);
    }

    void Listener::exitInvokeExpression(HooParser::InvokeExpressionContext *context) {
        HooBaseListener::exitInvokeExpression(context);
    }

    void Listener::enterExpressionList(HooParser::ExpressionListContext *context) {
        HooBaseListener::enterExpressionList(context);
    }

    void Listener::exitExpressionList(HooParser::ExpressionListContext *context) {
        HooBaseListener::exitExpressionList(context);
    }

    void Listener::enterFunctionDefintion(HooParser::FunctionDefintionContext *context) {
        HooBaseListener::enterFunctionDefintion(context);
    }

    void Listener::exitFunctionDefintion(HooParser::FunctionDefintionContext *context) {
        HooBaseListener::exitFunctionDefintion(context);
    }

    void Listener::enterStatement(HooParser::StatementContext *context) {
        HooBaseListener::enterStatement(context);
    }

    void Listener::exitStatement(HooParser::StatementContext *context) {
        HooBaseListener::exitStatement(context);
    }

    void Listener::enterInvokeStatement(HooParser::InvokeStatementContext *context) {
        HooBaseListener::enterInvokeStatement(context);
    }

    void Listener::exitInvokeStatement(HooParser::InvokeStatementContext *context) {
        HooBaseListener::exitInvokeStatement(context);
    }

    void Listener::enterVariableDeclaraionStatement(HooParser::VariableDeclaraionStatementContext *context) {
        HooBaseListener::enterVariableDeclaraionStatement(context);
    }

    void Listener::exitVariableDeclaraionStatement(HooParser::VariableDeclaraionStatementContext *context) {
        HooBaseListener::exitVariableDeclaraionStatement(context);
    }

    void Listener::enterAssignmentStatement(HooParser::AssignmentStatementContext *context) {
        HooBaseListener::enterAssignmentStatement(context);
    }

    void Listener::exitAssignmentStatement(HooParser::AssignmentStatementContext *context) {
        HooBaseListener::exitAssignmentStatement(context);
    }

    void Listener::enterCompoundStatement(HooParser::CompoundStatementContext *context) {
        HooBaseListener::enterCompoundStatement(context);
    }

    void Listener::exitCompoundStatement(HooParser::CompoundStatementContext *context) {
        HooBaseListener::exitCompoundStatement(context);
    }

    void Listener::enterReturnStatement(HooParser::ReturnStatementContext *context) {
        HooBaseListener::enterReturnStatement(context);
    }

    void Listener::exitReturnStatement(HooParser::ReturnStatementContext *context) {
        HooBaseListener::exitReturnStatement(context);
    }

    void Listener::enterClassDefinition(HooParser::ClassDefinitionContext *context) {
        HooBaseListener::enterClassDefinition(context);
    }

    void Listener::exitClassDefinition(HooParser::ClassDefinitionContext *context) {
        HooBaseListener::exitClassDefinition(context);
    }

    void Listener::enterClassBody(HooParser::ClassBodyContext *context) {
        HooBaseListener::enterClassBody(context);
    }

    void Listener::exitClassBody(HooParser::ClassBodyContext *context) {
        HooBaseListener::exitClassBody(context);
    }

    void Listener::enterClassBodyItem(HooParser::ClassBodyItemContext *context) {
        HooBaseListener::enterClassBodyItem(context);
    }

    void Listener::exitClassBodyItem(HooParser::ClassBodyItemContext *context) {
        HooBaseListener::exitClassBodyItem(context);
    }

    void Listener::enterMethod(HooParser::MethodContext *context) {
        HooBaseListener::enterMethod(context);
    }

    void Listener::exitMethod(HooParser::MethodContext *context) {
        HooBaseListener::exitMethod(context);
    }

    void Listener::enterField(HooParser::FieldContext *context) {
        HooBaseListener::enterField(context);
    }

    void Listener::exitField(HooParser::FieldContext *context) {
        HooBaseListener::exitField(context);
    }

    void Listener::enterNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *context) {
        HooBaseListener::enterNamespaceDeclaraion(context);
    }

    void Listener::exitNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *context) {
        HooBaseListener::exitNamespaceDeclaraion(context);
    }

    void Listener::enterUseSpecifier(HooParser::UseSpecifierContext *context) {
        HooBaseListener::enterUseSpecifier(context);
    }

    void Listener::exitUseSpecifier(HooParser::UseSpecifierContext *context) {
        HooBaseListener::exitUseSpecifier(context);
    }

    void Listener::enterUnit(HooParser::UnitContext *context) {
        HooBaseListener::enterUnit(context);
    }

    void Listener::exitUnit(HooParser::UnitContext *context) {
        HooBaseListener::exitUnit(context);
    }

    void Listener::enterEveryRule(antlr4::ParserRuleContext *context) {
        HooBaseListener::enterEveryRule(context);
    }

    void Listener::exitEveryRule(antlr4::ParserRuleContext *context) {
        HooBaseListener::exitEveryRule(context);
    }

    void Listener::visitTerminal(antlr4::tree::TerminalNode *node) {
        HooBaseListener::visitTerminal(node);
    }

    void Listener::visitErrorNode(antlr4::tree::ErrorNode *node) {
        HooBaseListener::visitErrorNode(node);
    }
}


