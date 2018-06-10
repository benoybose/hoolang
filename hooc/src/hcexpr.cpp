#include "hcexpr.hh"

namespace hooc {
    Expression::Expression(hooc::ExpressionType expressionType)
            : Node(NodeType::HC_NODE_EXPRESSION) {
        this->_expressionType = expressionType;
    }

    ExpressionType Expression::getExpressionType() {
        return this->_expressionType;
    }
}