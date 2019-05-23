//
// Created by benoybose on 5/23/19.
//

#ifndef HC_INVOKEEXPRESSION_H
#define HC_INVOKEEXPRESSION_H

#include "Expression.hh"

#include <list>

namespace hooc {
    namespace ast {
        class InvokeExpression: public Expression {
        private:
            Expression* _receiver;
            std::list<Expression*> _arguments;
        public:
            InvokeExpression(Expression* receiver, std::list<Expression*> arguments);

        public:
            const Expression* GetReceiver() const;
            const std::list<Expression*> GetArguments() const;
        };
    }
}



#endif //HC_INVOKEEXPRESSION_H
