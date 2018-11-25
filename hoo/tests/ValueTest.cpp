#define BOOST_TEST_MODULE Value Test
#include <boost/test/included/unit_test.hpp>
#include "Value.hh"
using namespace hoo;

BOOST_AUTO_TEST_CASE(integer_value_test) {
    Value integerValue = Value::MakeInteger(456019);
    BOOST_CHECK(VALUE_INTEGER == integerValue.GetType());
    BOOST_CHECK(456019 == integerValue.GetInteger());
    BOOST_CHECK(integerValue.GetTypeName() == TYPENAME_INTEGER);
}

BOOST_AUTO_TEST_CASE(boolean_value_test) {
    Value booleanValue = Value::MakeBoolean(true);
    BOOST_CHECK(VALUE_BOOLEAN == booleanValue.GetType());
    BOOST_CHECK(true == booleanValue.GetBoolean());

    booleanValue = Value::MakeBoolean(false);
    BOOST_CHECK(VALUE_BOOLEAN == booleanValue.GetType());
    BOOST_CHECK(false == booleanValue.GetBoolean());
    BOOST_CHECK(booleanValue.GetTypeName() == TYPENAME_BOOLEAN);
}

BOOST_AUTO_TEST_CASE(double_value_test) {
    Value doubleValue = Value::MakeDouble(3.14);
    BOOST_CHECK(VALUE_DOUBLE == doubleValue.GetType());
    BOOST_CHECK(3.14 == doubleValue.GetDouble());
    BOOST_CHECK(doubleValue.GetTypeName() == TYPENAME_DOUBLE);
}

BOOST_AUTO_TEST_CASE(object_value_test) {
//    String *text = new String("Hello, World");
//    Value stringValue = Value::MakeObject(text);
//    BOOST_CHECK(VALUE_OBJECT == stringValue.GetType());
//    auto object = stringValue.GetObject();
//    BOOST_CHECK((nullptr != object));
//    BOOST_CHECK(0 == object->GetTypeName().compare(TYPENAME_STRING));
//    String *stringClass = static_cast<String *>(object);
//    BOOST_CHECK(nullptr != stringClass);
//    BOOST_CHECK(0 == stringClass->GetValue().compare("Hello, World"));
//    BOOST_CHECK(stringValue.GetTypeName() == TYPENAME_STRING);
}

BOOST_AUTO_TEST_CASE(string_value_test) {
    Value stringValue = Value::MakeString("Hello, World");
    BOOST_CHECK(VALUE_STRING == stringValue.GetType());
    BOOST_CHECK(0 == stringValue.GetString().compare("Hello, World"));
    BOOST_CHECK(stringValue.GetTypeName() == TYPENAME_STRING);
}

BOOST_AUTO_TEST_CASE(byte_value_test) {
    Value byteValue = Value::MakeByte(45);
    BOOST_CHECK(VALUE_BYTE == byteValue.GetType());
    BOOST_CHECK(45 == byteValue.GetByte());
}

BOOST_AUTO_TEST_CASE(character_value_test) {
    Value charValue = Value::MakeCharacter(0x40, 0, 0, 0);
    BOOST_CHECK(VALUE_CHARACTER == charValue.GetType());
    BOOST_CHECK(1 == charValue.GetCharacter().GetSize());
    BOOST_CHECK(0x40 == charValue.GetCharacter().at(0));

    charValue = Value::MakeCharacter(0xC2, 0xA2, 0, 0);
    BOOST_CHECK(VALUE_CHARACTER == charValue.GetType());
    BOOST_CHECK(2 == charValue.GetCharacter().GetSize());
    BOOST_CHECK(0xC2 == charValue.GetCharacter().at(0));
    BOOST_CHECK(0xA2 == charValue.GetCharacter().at(1));

    charValue = Value::MakeCharacter(0xE2, 0x82, 0xAC, 0);
    BOOST_CHECK(VALUE_CHARACTER == charValue.GetType());
    BOOST_CHECK(3 == charValue.GetCharacter().GetSize());
    BOOST_CHECK(0xE2 == charValue.GetCharacter().at(0));
    BOOST_CHECK(0x82 == charValue.GetCharacter().at(1));
    BOOST_CHECK(0xAC == charValue.GetCharacter().at(2));


    charValue = Value::MakeCharacter(0xF0, 0x90, 0x8D, 0x88);
    BOOST_CHECK(VALUE_CHARACTER == charValue.GetType());
    BOOST_CHECK(4 == charValue.GetCharacter().GetSize());
    BOOST_CHECK(0xF0 == charValue.GetCharacter().at(0));
    BOOST_CHECK(0x90 == charValue.GetCharacter().at(1));
    BOOST_CHECK(0x8D == charValue.GetCharacter().at(2));
    BOOST_CHECK(0x88 == charValue.GetCharacter().at(3));
}
