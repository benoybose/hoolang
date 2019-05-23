//
// Created by benoybose on 5/23/19.
//

#include "InvokeExpression.h"

namespace hooc {
    namespace ast {
        InvokeExpression::InvokeExpression(Expression *receiver, std::list<Expression *> arguments) :
                Expression(EXPRESSION_INVOKE),
                _receiver(receiver),
                _arguments(arguments) {
        }

        const Expression *InvokeExpression::GetReceiver() const {
            return this->_receiver;
        }

        const std::list<Expression *> InvokeExpression::GetArguments() const {
            return this->_arguments;
        }
    }
}
