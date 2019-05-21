//
// Created by benoy on 5/21/2019.
//

#ifndef ARRAYACCESSEXPRESSION_HH
#define ARRAYACCESSEXPRESSION_HH

#include "Expression.hh"

namespace hooc {
    namespace ast {
        class ArrayAccessExpression: public Expression {
        private:
            Expression* _container;
            Expression* _index;

        public:
            ArrayAccessExpression(Expression* container, Expression* index);

        public:
            const Expression* GetContainer() const;
            const Expression* GetIndex() const;
        };
    }
}




#endif //PROJECT_ARRAYACCESSEXPRESSION_HH
