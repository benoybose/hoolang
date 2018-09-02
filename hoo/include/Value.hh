#ifndef PROJECT_VALUE_HH
#define PROJECT_VALUE_HH

#include "HooTypes.hh"
#include "Object.hh"
#include "String.hh"

#include <boost/variant.hpp>
#include <memory>

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

    class Value : public boost::variant<Byte, Boolean, Integer, Character, String, Double, Object *> {

    public:
        Value(const Value& value);

    public:
        Value& operator = (const Value& value);

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
