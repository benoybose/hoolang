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

#include "Statement.hh"

namespace hooc {
    namespace ast {
        Statement::Statement(StatementType statementType) :
                RootStatement(ROOTSTMT_STATEMENT),
                _statementType(statementType) {
        }

        const StatementType Statement::GetStatementType() const {
            return this->_statementType;
        }

        CompoundStatement::CompoundStatement(std::list<Statement *> &statements) :
                Statement(STMT_COMPOUND) {
            for (auto statement: statements) {
                this->_statements.push_back(statement);
            }
        }

        const std::list<Statement *> &CompoundStatement::GetStatements() const {
            return this->_statements;
        }

        ReturnStatement::ReturnStatement(Expression *expression) :
                ExpressionStatement(expression, STMT_RETURN) {
        }

        AssignmentStatement::AssignmentStatement(Expression *primaryExpression,
                                                 Expression *valueExpression) : Statement(STMT_ASSIGNMENT),
                                                                                _primaryExpression(primaryExpression),
                                                                                _valueExpression(valueExpression) {
        }

        const Expression *AssignmentStatement::GetPrimaryExpression() const {
            return this->_primaryExpression;
        }

        const Expression *AssignmentStatement::GetValueExpression() const {
            return this->_valueExpression;
        }

        VariableDeclarationStatement::VariableDeclarationStatement(Declaration *declaration) :
                Statement(STMT_VARIABLE_DECLARATION),
                _declaration(declaration) {

        }

        const Declaration *VariableDeclarationStatement::GetDeclaration() const {
            return this->_declaration;
        }

        InvokeStatement::InvokeStatement(InvokeExpression *expression) :
                ExpressionStatement(expression, STMT_INVOKE) {
        }

        ExpressionStatement::ExpressionStatement(Expression *expression, StatementType statementType) :
                Statement(statementType),
                _expression(expression) {

        }

        const Expression *ExpressionStatement::GetExpression() const {
            return this->_expression;
        }

        NoopStatement::NoopStatement(): Statement(STMT_NOOP) {
        }
    }
}