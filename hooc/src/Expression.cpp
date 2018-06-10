#include "Expression.hh"

namespace hooc {
    Expression::Expression() : Node(NodeType::HC_NODE_EXPRESSION) {
        this->_expressionType = hooc::ExpressionType::InvalidExpr;
    }

    Expression::Expression(hooc::ExpressionType expressionType)
            : Node(NodeType::HC_NODE_EXPRESSION) {
        this->_expressionType = expressionType;
    }

    Expression::Expression(const hooc::Expression &expression): Node(hooc::NodeType::HC_NODE_EXPRESSION) {
        this->_expressionType = expression._expressionType;
    }

    ExpressionType Expression::getExpressionType() {
        return this->_expressionType;
    }
}