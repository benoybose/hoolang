#ifndef PROJECT_VALUE_HH
#define PROJECT_VALUE_HH

#include "HooTypes.hh"
#include "Object.hh"
#include "String.hh"
#include "Character.hh"

#include <boost/variant.hpp>
#include <memory>

namespace hoo {
    extern const std::string TYPENAME_INTEGER; // = "hoo.integer";
    extern const std::string TYPENAME_BOOLEAN; // = "hoo.boolean";
    extern const std::string TYPENAME_DOUBLE; // = "hoo.double";
    extern const std::string TYPENAME_BYTE; // = "hoo.byte";

    typedef enum {
        VALUE_BYTE,
        VALUE_BOOLEAN,
        VALUE_INTEGER,
        VALUE_OBJECT,
        VALUE_DOUBLE,
        VALUE_CHARACTER,
        VALUE_STRING
    } ValueType;

    class Value {
    private:
        typedef boost::variant<Byte,
                Boolean,
                Integer,
                Character,
                String,
                Double,
                Object *> ValueVariant;

    private:
        ValueVariant _value;

    public:
        Value(const Value &value);

        Value(Byte value);

        Value(Boolean value);

        Value(Integer integer);

        Value(Character value);

        Value(String value);

        Value(Double value);

        Value(Object *value);

    public:
        static Value MakeByte(Byte value);

        static Value MakeBoolean(Boolean value);

        static Value MakeInteger(Integer value);

        static Value MakeCharacter(uint8_t byte0 = 0x0,
                uint8_t byte1 = 0x0,
                uint8_t byte2 = 0x0,
                uint8_t byte3 = 0x0);

        static Value MakeString(String value);

        static Value MakeDouble(Double value);

        static Value MakeObject(Object *value);

    public:
        Value &operator=(const Value &value);

    public:
        ValueType GetType() const;

        const std::string &GetTypeName() const;

        Integer GetInteger() const;

        Character GetCharacter() const;

        String GetString() const;

        Boolean GetBoolean() const;

        Double GetDouble() const;

        Byte GetByte() const;

        Object *GetObject() const;

    private:
        std::string _typename;
    };

    typedef std::shared_ptr<Value> ValuePtr;
}
#endif //PROJECT_VALUE_HH
