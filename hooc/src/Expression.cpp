#include "Expression.hh"

namespace hooc {
    Expression::Expression(hooc::ExpressionType expressionType)
            : Node(NodeType::ExpressionNode) {
        this->_expressionType = expressionType;
    }

    ExpressionType Expression::GetExpressionType() {
        return this->_expressionType;
    }

    std::string Expression::GetExpressionTypeName() {
        switch(this->_expressionType) {
            case hooc::ExpressionType ::InvalidExpr: return "Invalid Expression";
            case hooc::ExpressionType ::BinaryExpr: return "Binary Expression";
            case hooc::ExpressionType ::LiteralExpr: return "Literal Expression";
            default: return "Unknown Expression";
        }
    }
}