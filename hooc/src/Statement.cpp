#include "Statement.hh"

namespace hooc {
    Statement::Statement(hooc::StatementType statementType):
            Node(NODE_STATEMENT),
            _statementType(statementType) {
    }

    StatementType Statement::GetStatementType() {
        return this->_statementType;
    }
}