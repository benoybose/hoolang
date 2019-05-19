//
// Created by benoy on 5/19/2019.
//

#include "Declaration.hh"

namespace hooc {
    namespace ast {
        Declaration::Declaration(std::string name,
                                 TypeSpecification *declared_type,
                                 void *initializer) :
                _name(name),
                _declared_type(declared_type),
                _initializer(initializer) {

        }

        Declaration::~Declaration() {
            if(nullptr != this->_declared_type) {
                delete this->_declared_type;
            }

            if(nullptr != this->_initializer) {
                delete this->_initializer;
            }
        }

        const TypeSpecification *Declaration::GetDelcaredType() const {
            return _declared_type;
        }

        const std::string &Declaration::GetName() const {
            return _name;
        }

        const void *Declaration::GetInitializer() const {
            return _initializer;
        }
    }
}
