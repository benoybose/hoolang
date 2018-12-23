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

#ifndef LISTENER_HH
#define LISTENER_HH

#include "HooBaseListener.h"
#include "Unit.hh"

namespace hooc
{
    class Listener: public HooBaseListener {
    private:
        CompilationUnit* _module;

    public:
        Listener();

    public:
        void enterPrimaryExpression(HooParser::PrimaryExpressionContext *context) override;

        void exitPrimaryExpression(HooParser::PrimaryExpressionContext *context) override;

        void enterExpression(HooParser::ExpressionContext *context) override;

        void exitExpression(HooParser::ExpressionContext *context) override;

        void enterBinaryOperator(HooParser::BinaryOperatorContext *context) override;

        void exitBinaryOperator(HooParser::BinaryOperatorContext *context) override;

        void enterArithmeticOperator(HooParser::ArithmeticOperatorContext *context) override;

        void exitArithmeticOperator(HooParser::ArithmeticOperatorContext *context) override;

        void enterRelationalOperator(HooParser::RelationalOperatorContext *context) override;

        void exitRelationalOperator(HooParser::RelationalOperatorContext *context) override;

        void enterAssignmentOperator(HooParser::AssignmentOperatorContext *context) override;

        void exitAssignmentOperator(HooParser::AssignmentOperatorContext *context) override;

        void enterTypeSepecifier(HooParser::TypeSepecifierContext *context) override;

        void exitTypeSepecifier(HooParser::TypeSepecifierContext *context) override;

        void enterDeclaration(HooParser::DeclarationContext *context) override;

        void exitDeclaration(HooParser::DeclarationContext *context) override;

        void enterParamList(HooParser::ParamListContext *context) override;

        void exitParamList(HooParser::ParamListContext *context) override;

        void enterInitializer(HooParser::InitializerContext *context) override;

        void exitInitializer(HooParser::InitializerContext *context) override;

        void enterInvokeExpression(HooParser::InvokeExpressionContext *context) override;

        void exitInvokeExpression(HooParser::InvokeExpressionContext *context) override;

        void enterExpressionList(HooParser::ExpressionListContext *context) override;

        void exitExpressionList(HooParser::ExpressionListContext *context) override;

        void enterFunctionDefintion(HooParser::FunctionDefintionContext *context) override;

        void exitFunctionDefintion(HooParser::FunctionDefintionContext *context) override;

        void enterStatement(HooParser::StatementContext *context) override;

        void exitStatement(HooParser::StatementContext *context) override;

        void enterInvokeStatement(HooParser::InvokeStatementContext *context) override;

        void exitInvokeStatement(HooParser::InvokeStatementContext *context) override;

        void enterVariableDeclaraionStatement(HooParser::VariableDeclaraionStatementContext *context) override;

        void exitVariableDeclaraionStatement(HooParser::VariableDeclaraionStatementContext *context) override;

        void enterAssignmentStatement(HooParser::AssignmentStatementContext *context) override;

        void exitAssignmentStatement(HooParser::AssignmentStatementContext *context) override;

        void enterCompoundStatement(HooParser::CompoundStatementContext *context) override;

        void exitCompoundStatement(HooParser::CompoundStatementContext *context) override;

        void enterReturnStatement(HooParser::ReturnStatementContext *context) override;

        void exitReturnStatement(HooParser::ReturnStatementContext *context) override;

        void enterClassDefinition(HooParser::ClassDefinitionContext *context) override;

        void exitClassDefinition(HooParser::ClassDefinitionContext *context) override;

        void enterClassBody(HooParser::ClassBodyContext *context) override;

        void exitClassBody(HooParser::ClassBodyContext *context) override;

        void enterClassBodyItem(HooParser::ClassBodyItemContext *context) override;

        void exitClassBodyItem(HooParser::ClassBodyItemContext *context) override;

        void enterMethod(HooParser::MethodContext *context) override;

        void exitMethod(HooParser::MethodContext *context) override;

        void enterField(HooParser::FieldContext *context) override;

        void exitField(HooParser::FieldContext *context) override;

        void enterNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *context) override;

        void exitNamespaceDeclaraion(HooParser::NamespaceDeclaraionContext *context) override;

        void enterUseSpecifier(HooParser::UseSpecifierContext *context) override;

        void exitUseSpecifier(HooParser::UseSpecifierContext *context) override;

        void enterUnit(HooParser::UnitContext *context) override;

        void exitUnit(HooParser::UnitContext *context) override;

        void enterEveryRule(antlr4::ParserRuleContext *context) override;

        void exitEveryRule(antlr4::ParserRuleContext *context) override;

        void visitTerminal(antlr4::tree::TerminalNode *node) override;

        void visitErrorNode(antlr4::tree::ErrorNode *node) override;
    };
}

#endif //PROJECT_LISTENER_HH
