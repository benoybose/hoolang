//
// Created by benoy on 5/21/2019.
//

#include "ArrayAccessExpression.hh"

namespace hooc {
    namespace ast {
        ArrayAccessExpression::ArrayAccessExpression(Expression *container, Expression *index) :
                Expression(EXPRESSION_ARRAY), _container(container), _index(index) {
        }

        const Expression *ArrayAccessExpression::GetContainer() const {
            return this->_container;
        }

        const Expression *ArrayAccessExpression::GetIndex() const {
            return this->_index;
        }
    }
}
