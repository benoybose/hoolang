#include "Value.hh"

#include <memory>
#include <exception>

namespace hoo {
    const std::string TYPENAME_INTEGER = "hoo.integer";
    const std::string TYPENAME_BOOLEAN = "hoo.boolean";
    const std::string TYPENAME_DOUBLE = "hoo.double";
    const std::string TYPENAME_BYTE = "hoo.byte";

    Value::Value(hoo::Integer integer) {
        ValueHolderPtr ptr(new IntegerValueHolder(integer));
        this->_value_holder = ptr;
    }

    Value::Value(std::string text) {
        ValueHolderPtr ptr(new StringValueHolder(text));
        this->_value_holder = ptr;
    }

    Value::Value(hoo::Boolean boolean) {
        ValueHolderPtr ptr(new BooleanValueHolder(boolean));
        this->_value_holder = ptr;
    }

    Value::Value(hoo::Double real) {
        ValueHolderPtr ptr(new DoubleValueHolder(real));
        this->_value_holder = ptr;
    }

    Value::Value(char byte0,
                 unsigned char byte1,
                 unsigned char byte2,
                 unsigned char byte3) {
        ValueHolderPtr ptr(new CharacterValueHolder(byte0, byte1, byte2, byte3));
        this->_value_holder = ptr;
    }

    Value::Value(hoo::Byte byte) {
        ValueHolderPtr ptr(new ByteValueHolder(byte));
        this->_value_holder = ptr;
    }

    Value::Value(hoo::Object *object) {
        ObjectPtr object_ptr(object);
        ValueHolderPtr ptr(new ObjectValueHolder(object_ptr));
        this->_value_holder = ptr;
    }

    Value::Value(const hoo::Value &value) {
        this->_value_holder = value._value_holder;
    }

    Value &hoo::Value::operator=(const hoo::Value &value) {
        this->_value_holder = value._value_holder;
        return *(this);
    }

    ValueType hoo::Value::GetType() const {
        ValueHolder *value_holder = this->_value_holder.get();
        if (nullptr != value_holder) {
            return value_holder->GetType();
        } else {
            throw std::runtime_error("Value is not initialized.");
        }
    }

    Integer hoo::Value::GetInteger() const {
        IntegerValueHolder *value_holder = static_cast<IntegerValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue();
        } else {
            return 0;
        }
    }

    Character hoo::Value::GetCharacter() const {
        CharacterValueHolder *value_holder = static_cast<CharacterValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue();
        } else {
            return nullptr;
        }
    }

    std::string hoo::Value::GetString() const {
        StringValueHolder *value_holder = static_cast<StringValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue();
        } else {
            return std::string("");
        }
    }

    Boolean hoo::Value::GetBoolean() const {
        BooleanValueHolder *value_holder = static_cast<BooleanValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue();
        } else {
            return false;
        }
    }

    Double Value::GetDouble() const {
        DoubleValueHolder *value_holder = static_cast<DoubleValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue();
        } else {
            return 0.0;
        }
    }

    Byte Value::GetByte() const {
        ByteValueHolder *value_holder = static_cast<ByteValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue();
        } else {
            return 0;
        }
    }

    Object *Value::GetObject() const {
        auto value_holder = static_cast<ObjectValueHolder *>(this->_value_holder.get());
        if (nullptr != value_holder) {
            return value_holder->GetValue().get();
        } else {
            return nullptr;
        }
    }

    Value Value::MakeInteger(hoo::Integer value) {
        return hoo::Value(value);
    }

    Value Value::MakeCharacter(char byte0,
                               unsigned char byte1,
                               unsigned char byte2,
                               unsigned char byte3) {
        return hoo::Value(byte0, byte1, byte2, byte3);
    }

    Value Value::MakeString(std::string string) {
        return hoo::Value(string);
    }

    Value Value::MakeBoolean(bool value) {
        return hoo::Value(value);
    }

    Value Value::MakeDouble(hoo::Double value) {
        return Value(value);
    }

    Value Value::MakeByte(hoo::Byte value) {
        return Value(value);
    }

    Value Value::MakeObject(hoo::Object *object) {
        return Value(object);
    }

    const std::string &hoo::Value::GetTypeName() const {
        const ValueType value_type = this->_value_holder->GetType();
        switch (value_type) {
            case VALUE_OBJECT: {
                ObjectValueHolder *value_holder = static_cast<ObjectValueHolder *> (this->_value_holder.get());
                return value_holder->GetValue()->GetTypeName();
            }
            case VALUE_INTEGER:
                return TYPENAME_INTEGER;
            case VALUE_BOOLEAN:
                return TYPENAME_BOOLEAN;
            case VALUE_DOUBLE:
                return TYPENAME_DOUBLE;
            case VALUE_BYTE:
                return TYPENAME_BYTE;
        }
    }
}