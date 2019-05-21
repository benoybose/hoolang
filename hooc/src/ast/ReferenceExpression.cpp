//
// Created by benoy on 5/21/2019.
//

#include "ReferenceExpression.hh"

namespace hooc {
    namespace ast {
        ReferenceExpression::ReferenceExpression(std::string &name) :
                Expression(EXPRESSION_REFERENCE),
                _name(name), _parent(nullptr) {

        }

        ReferenceExpression::ReferenceExpression(const std::string &name) :
                Expression(EXPRESSION_REFERENCE),
                _name(name), _parent(nullptr) {

        }

        ReferenceExpression::ReferenceExpression(ReferenceExpression *parent,
                                                 std::string &name) :
                Expression(EXPRESSION_REFERENCE),
                _parent(nullptr), _name(name) {

        }

        ReferenceExpression::ReferenceExpression(ReferenceExpression *parent,
                                                 const std::string &name) :
                Expression(EXPRESSION_REFERENCE),
                _parent(nullptr), _name(name) {

        }

        const std::string &ReferenceExpression::GetName() const {
            return this->_name;
        }

        const ReferenceExpression *ReferenceExpression::GetParent() const {
            return this->_parent;
        }
    }
}
