//
// Created by benoybose on 23/12/18.
//

#include <Class.hh>

#include "Class.hh"

namespace hooc {
    Class::Class(): _name("") {
    }

    Class::Class(std::string name): _name(name) {
    }

    const std::string &Class::GetName() const {
        return this->_name;
    }
}
