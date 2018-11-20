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
        const int type = this->_value.which();
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
        return boost::get<Integer>(this->_value);
    }

    Character hoo::Value::GetCharacter() const {
        auto value = boost::get<Character>(this->_value);
        return value;
    }

    String hoo::Value::GetString() const {
        auto value = boost::get<String>(this->_value);
        return value;
    }

    Boolean hoo::Value::GetBoolean() const {
        auto value = boost::get<Boolean>(this->_value);
        return value;
    }

    Double Value::GetDouble() const {
        auto value = boost::get<Double>(this->_value);
        return value;
    }

    Byte Value::GetByte() const {
        auto value = boost::get<Byte>(this->_value);
        return value;
    }

    Object *Value::GetObject() const {
        auto value = boost::get<Object*>(this->_value);
        return value;
    }

    const std::string &hoo::Value::GetTypeName() const {
        const int type = this->_value.which();
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

    Value::Value(const Value &value):
            _value(this->_value) {
    }

    Value &Value::operator=(const Value &value) {
        this->_value = value._value;
    }

    Value::Value(Byte value): _value(value) {
    }

    Value::Value(Boolean value): _value(value) {
    }

    Value::Value(Integer integer): _value(integer) {
    }

    Value::Value(Character value): _value(value) {
    }

    Value::Value(String value): _value(value) {
    }

    Value::Value(Double value): _value(value) {
    }

    Value::Value(Object *value): _value(value) {
    }

    Value Value::MakeByte(Byte value) {
        return Value((Byte) value);
    }

    Value Value::MakeBoolean(Boolean value) {
        return Value((Boolean) value);
    }

    Value Value::MakeInteger(Integer value) {
        return Value((Integer) value);
    }

    Value Value::MakeCharacter(Character value) {
        return Value((Character) value);
    }

    Value Value::MakeString(String value) {
        return Value((String) value);
    }

    Value Value::MakeDouble(Double value) {
        return Value((Double) value);
    }

    Value Value::MakeObject(Object *value) {
        return Value(value);
    }
}