#include "Object.hh"

namespace hoo {

    Object::Object(const std::string &type_name) {
        this->_type_name = type_name;
    }

    const std::string &Object::GetTypeName() const {
        return this->_type_name;
    }
}