#include "Value.hh"

#include <memory>
#include <exception>
#include <boost/variant.hpp>

namespace hoo {
    const std::string TYPENAME_INTEGER = "hoo.integer";
    const std::string TYPENAME_BOOLEAN = "hoo.boolean";
    const std::string TYPENAME_DOUBLE = "hoo.double";
    const std::string TYPENAME_BYTE = "hoo.byte";

    ValueType hoo::Value::GetType() const {
        const int type = this->which();
        switch (type) {
            case 0:
                return VALUE_BYTE;
            case 1:
                return VALUE_BOOLEAN;
            case 2:
                return VALUE_INTEGER;
            case 3:
                return VALUE_OBJECT;
            case 4:
                return VALUE_OBJECT;
            case 5:
                return VALUE_DOUBLE;
            case 6:
                return VALUE_OBJECT;
        }
    }

    Integer hoo::Value::GetInteger() const {
        return boost::get<Integer>(*this);
    }

    Character hoo::Value::GetCharacter() const {
        auto value = boost::get<Character>(*this);
        return value;
    }

    String hoo::Value::GetString() const {
        auto value = boost::get<String>(*this);
        return value;
    }

    Boolean hoo::Value::GetBoolean() const {
        auto value = boost::get<Boolean>(*this);
        return value;
    }

    Double Value::GetDouble() const {
        auto value = boost::get<Double>(*this);
        return value;
    }

    Byte Value::GetByte() const {
        auto value = boost::get<Byte>(*this);
        return value;
    }

    Object *Value::GetObject() const {
        auto value = boost::get<Object*>(*this);
        return value;
    }

    const std::string &hoo::Value::GetTypeName() const {
        const int type = this->which();
        switch (type) {
            case 0:
                return TYPENAME_BYTE;
            case 1:
                return TYPENAME_BOOLEAN;
            case 2:
                return TYPENAME_INTEGER;
            case 3:
                return TYPENAME_CHARACTER;
            case 4:
                return TYPENAME_STRING;
            case 5:
                return TYPENAME_DOUBLE;
            case 6:
            {
                auto object = this->GetObject();
                if(nullptr != object) {
                    return object->GetTypeName();
                } else {
                    return this->_typename;
                }
            }
        }
    }

    Value::Value(const Value &value) {
        this->operator=(value);
    }

    Value &Value::operator=(const Value &value) {
        this->operator=(value);
        return *this;
    }
}