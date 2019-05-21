#include "Expression.hh"

namespace hooc {
    namespace ast {
        Expression::Expression(ExpressionType expressionType) {
            this->_expressionType = expressionType;
        }

        const ExpressionType Expression::GetExpressionType() const {
            return this->_expressionType;
        }
    }
}