#include "hcstmt.hh"

namespace hooc {
    Statement::Statement():
            Node(NodeType::StatementNode),
            _statementType(StatementType::InvalidStateMent) {
    }

    Statement::Statement(hooc::StatementType statementType):
            _statementType(statementType) {
    }

    StatementType Statement::GetStatementType() {
        return this->_statementType;
    }

    std::string Statement::GetStatementTypeName() {
        switch(this->_statementType) {
            case StatementType ::InvalidStateMent: return "Invalid Statement";
            case StatementType ::ExpressionStatement: return "Expression Statement";
            default: return "Unknown Statement";
        }
    }
}