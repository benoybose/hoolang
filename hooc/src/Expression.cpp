#include "Expression.hh"

namespace hooc {
    Expression::Expression() : Node(NodeType::ExpressionNode) {
        this->_expressionType = hooc::ExpressionType::InvalidExpr;
    }

    Expression::Expression(hooc::ExpressionType expressionType)
            : Node(NodeType::ExpressionNode) {
        this->_expressionType = expressionType;
    }

    Expression::Expression(const hooc::Expression &expression): Node(hooc::NodeType::ExpressionNode) {
        this->_expressionType = expression._expressionType;
    }

    ExpressionType Expression::getExpressionType() {
        return this->_expressionType;
    }
}