//
// Created by benoy on 5/16/2019.
//

#include "RootStatement.hh"

namespace hooc {
    namespace ast {
        RootStatement::RootStatement(ROOT_STATEMENT_TYPE type)
                : _type(type) {

        }

        const ROOT_STATEMENT_TYPE RootStatement::GetType() const {
            return Interface;
        }
    }
}
