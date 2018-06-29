//
// Created by COMP on 27-06-2018.
//

#include "StringClass.hh"

#include <string>

namespace hoo {
    const std::string TYPENAME_STRING = "hoo.string";

    StringClass::StringClass(): Object(TYPENAME_STRING), _value("") {}

    StringClass::StringClass(const std::string &text):
            Object(TYPENAME_STRING),
            _value(text) {}

    StringClass::StringClass(const char *text):
            Object(TYPENAME_STRING),
            _value(std::string(text)) {
    }

    const std::string &hoo::StringClass::GetValue() const {
        return _value;
    }
}