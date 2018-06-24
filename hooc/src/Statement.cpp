#include "Statement.hh"

namespace hooc {
    Statement::Statement(hooc::StatementType statementType):
            Node(NodeType::StatementNode),
            _statementType(statementType) {
    }

    StatementType Statement::GetStatementType() {
        return this->_statementType;
    }

    std::string Statement::GetStatementTypeName() {
        switch(this->_statementType) {
            case StatementType ::InvalidStmt : return "Invalid Statement";
            case StatementType ::ExpressionStmt : return "Expression Statement";
            default: return "Unknown Statement";
        }
    }
}