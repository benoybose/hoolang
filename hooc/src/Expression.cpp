#include "Expression.hh"

namespace hooc {
    Expression::Expression(hooc::ExpressionType expressionType)
            : Node(NODE_EXPRESSION) {
        this->_expressionType = expressionType;
    }

    ExpressionType Expression::GetExpressionType() {
        return this->_expressionType;
    }
}