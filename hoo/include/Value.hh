//
// Created by COMP on 26-06-2018.
//

#include "HooTypes.hh"
#include "Object.hh"
#include "StringClass.hh"

#include <memory>

#ifndef PROJECT_VALUE_HH
#define PROJECT_VALUE_HH
namespace hoo {
    extern const std::string TYPENAME_INTEGER; // = "hoo.integer";
    extern const std::string TYPENAME_BOOLEAN; // = "hoo.boolean";
    extern const std::string TYPENAME_DOUBLE; // = "hoo.double";
    extern const std::string TYPENAME_BYTE; // = "hoo.byte";

    typedef enum {
        VALUE_OBJECT,
        VALUE_INTEGER,
        VALUE_BOOLEAN,
        VALUE_DOUBLE,
        VALUE_BYTE
    } ValueType;

    class Value {
    private:
        class ValueHolder {
        private:
            ValueType _type;
            bool _is_object;
        public:
            explicit ValueHolder(ValueType value_type) : _type(value_type), _is_object(false) {}
            ValueHolder(ObjectPtr object) : _type(VALUE_OBJECT), _is_object(true) {}

        public:
            inline ValueType GetType() const { return this->_type; }
        };

        class IntegerValueHolder : public ValueHolder {
        private:
            Integer _value;
        public:
            explicit IntegerValueHolder(Integer value) : ValueHolder(VALUE_INTEGER), _value(value) {}

        public:
            inline Integer GetValue() const { return _value; }
        };

        class ObjectValueHolder : public ValueHolder {
        private:
            ObjectPtr _object;

        public:
            explicit ObjectValueHolder(ObjectPtr object) :
                    ValueHolder(VALUE_OBJECT), _object(object) {}

        public:
            inline ObjectPtr GetValue() const { return _object; }
        };

        class StringValueHolder : public ObjectValueHolder {
        public:
            explicit StringValueHolder(std::string value) :
                    ObjectValueHolder(ObjectPtr(new StringClass(value))) {}

        public:
            inline std::string GetValue() {
                auto object = (StringClass*) (ObjectValueHolder::GetValue().get());
                return object->GetValue();
            }
        };

        class CharacterValueHolder : public ObjectValueHolder {
        public:
            CharacterValueHolder(unsigned char byte0,
                                 unsigned char byte1 = 0,
                                 unsigned char byte2 = 0,
                                 unsigned char byte3 = 0):
                    ObjectValueHolder(ObjectPtr(new CharacterClass(byte0, byte1, byte2, byte3))) {}

        public:
            inline Character GetValue() const {
                auto object = (CharacterClass*) (ObjectValueHolder::GetValue().get());
                return object;
            }
        };

        class BooleanValueHolder : public ValueHolder {
        private:
            Boolean _value;
        public:
            explicit BooleanValueHolder(Boolean value) : ValueHolder(VALUE_BOOLEAN), _value(value) {}

        public:
            inline Boolean GetValue() const { return _value; }
        };

        class DoubleValueHolder : public ValueHolder {
        private:
            Double _value;
        public:
            explicit DoubleValueHolder(Double value) : ValueHolder(VALUE_DOUBLE), _value(value) {}

        public:
            inline Double GetValue() const { return _value; }
        };

        class ByteValueHolder: public ValueHolder {
        private:
            Byte _value;
        public:
            explicit ByteValueHolder(Byte value): ValueHolder(VALUE_BYTE), _value(value) {}
        public:
            inline Byte GetValue() const { return _value; }
        };

        typedef std::shared_ptr<hoo::Value::ValueHolder> ValueHolderPtr;

    public:
        Value(const Value &value);
        Value &operator=(const Value &value);

    private:
        ValueHolderPtr _value_holder;

    public:
        static Value MakeInteger(Integer value);
        static Value MakeCharacter(char byte0, unsigned char byte1,
                                   unsigned char byte2, unsigned char byte3);
        static Value MakeString(std::string string);
        static Value MakeBoolean(bool value);
        static Value MakeDouble(Double value);
        static Value MakeByte(Byte value);
        static Value MakeObject(Object* object);

    private:
        explicit Value(Integer integer);

        explicit Value(std::string string);

        explicit Value(Boolean boolean);

        explicit Value(Double real);

        explicit Value(char byte0,
                unsigned char byte1 = 0,
                unsigned char byte2 = 0,
                unsigned char byte3 = 0);

        explicit Value(Byte byte);

        explicit Value(Object* object);

    public:
        ValueType GetType() const;
        const std::string& GetTypeName() const;

        Integer GetInteger() const;

        Character GetCharacter() const;

        std::string GetString() const;

        Boolean GetBoolean() const;

        Double GetDouble() const;

        Byte GetByte() const;

        Object* GetObject() const;
    };

    typedef std::shared_ptr<Value> ValuePtr;
}
#endif //PROJECT_VALUE_HH
