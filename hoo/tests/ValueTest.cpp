//
// Created by COMP on 27-06-2018.
//

#include "ValueTest.hh"
#include "Value.hh"
#include "StringClass.hh"

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
using namespace CppUnit;
using namespace hoo;
Test* ValueTest::suite() {
    TestSuite *value_test_suite = new TestSuite();
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test001_IntegerValue",
                                                         &ValueTest::Test001_IntegerValue));
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test002_BooleanValue",
                                                         &ValueTest::Test002_BooleanValue));
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test003_DoubleValue",
                                                         &ValueTest::Test003_DoubleValue));
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test004_ObjectValue",
                                                         &ValueTest::Test004_ObjectValue));
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test005_StringValue",
                                                         &ValueTest::Test005_StringValue));
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test006_ByteValue",
                                                         &ValueTest::Test006_ByteValue));
    value_test_suite->addTest(new TestCaller<ValueTest> ("Test007_CharacterValue",
                                                         &ValueTest::Test007_CharacterValue));
    return value_test_suite;
}

void ValueTest::Test001_IntegerValue() {
    Value integerValue = Value::MakeInteger(456019);
    CPPUNIT_ASSERT(VALUE_INTEGER == integerValue.GetType());
    CPPUNIT_ASSERT(456019 == integerValue.GetInteger());
    CPPUNIT_ASSERT(integerValue.GetTypeName() == TYPENAME_INTEGER);
}

void ValueTest::Test002_BooleanValue() {
    Value booleanValue = Value::MakeBoolean(true);
    CPPUNIT_ASSERT(VALUE_BOOLEAN == booleanValue.GetType());
    CPPUNIT_ASSERT(true == booleanValue.GetBoolean());

    booleanValue = Value::MakeBoolean(false);
    CPPUNIT_ASSERT(VALUE_BOOLEAN == booleanValue.GetType());
    CPPUNIT_ASSERT(false == booleanValue.GetBoolean());
    CPPUNIT_ASSERT(booleanValue.GetTypeName() == TYPENAME_BOOLEAN);
}

void ValueTest::Test003_DoubleValue() {
    Value doubleValue = Value::MakeDouble(3.14);
    CPPUNIT_ASSERT(VALUE_DOUBLE == doubleValue.GetType());
    CPPUNIT_ASSERT(3.14 == doubleValue.GetDouble());
    CPPUNIT_ASSERT(doubleValue.GetTypeName() == TYPENAME_DOUBLE);
}

void ValueTest::Test004_ObjectValue() {
    StringClass* text = new StringClass("Hello, World");
    Value stringValue = Value::MakeObject(text);
    CPPUNIT_ASSERT(VALUE_OBJECT == stringValue.GetType());
    auto object = stringValue.GetObject();
    CPPUNIT_ASSERT((nullptr != object));
    CPPUNIT_ASSERT(0 == object->GetTypeName().compare(TYPENAME_STRING));
    StringClass* stringClass = static_cast<StringClass*>(object);
    CPPUNIT_ASSERT(nullptr != stringClass);
    CPPUNIT_ASSERT(0 == stringClass->GetValue().compare("Hello, World"));
    CPPUNIT_ASSERT(stringValue.GetTypeName() == TYPENAME_STRING);
}

void ValueTest::Test005_StringValue() {
    Value stringValue = Value::MakeString("Hello, World");
    CPPUNIT_ASSERT(VALUE_OBJECT == stringValue.GetType());
    CPPUNIT_ASSERT(0 == stringValue.GetString().compare("Hello, World"));
    CPPUNIT_ASSERT(stringValue.GetTypeName() == TYPENAME_STRING);
}

void ValueTest::Test006_ByteValue() {
    Value byteValue = Value::MakeByte(45);
    CPPUNIT_ASSERT(VALUE_BYTE == byteValue.GetType());
    CPPUNIT_ASSERT(45 == byteValue.GetByte());
}

void ValueTest::Test007_CharacterValue() {
    Value charValue = Value::MakeCharacter('A', 0, 0, 0);
    CPPUNIT_ASSERT(VALUE_OBJECT == charValue.GetType());
    CPPUNIT_ASSERT('A' == (char) charValue.GetCharacter()->GetByte0());
    CPPUNIT_ASSERT(0 == charValue.GetCharacter()->GetByte1());
    CPPUNIT_ASSERT(0 == charValue.GetCharacter()->GetByte2());
    CPPUNIT_ASSERT(0 == charValue.GetCharacter()->GetByte3());
    CPPUNIT_ASSERT(1 == charValue.GetCharacter()->GetSize());

    charValue = Value::MakeCharacter(0xC2, 0xA2, 0, 0);
    CPPUNIT_ASSERT(VALUE_OBJECT == charValue.GetType());
    CPPUNIT_ASSERT(0xC2 == charValue.GetCharacter()->GetByte0());
    CPPUNIT_ASSERT(0xA2 == charValue.GetCharacter()->GetByte1());
    CPPUNIT_ASSERT(0 == charValue.GetCharacter()->GetByte2());
    CPPUNIT_ASSERT(0 == charValue.GetCharacter()->GetByte3());
    CPPUNIT_ASSERT(2 == charValue.GetCharacter()->GetSize());

    charValue = Value::MakeCharacter(0xE2, 0x82, 0xAC, 0);
    CPPUNIT_ASSERT(VALUE_OBJECT == charValue.GetType());
    CPPUNIT_ASSERT(0xE2 == charValue.GetCharacter()->GetByte0());
    CPPUNIT_ASSERT(0x82 == charValue.GetCharacter()->GetByte1());
    CPPUNIT_ASSERT(0xAC == charValue.GetCharacter()->GetByte2());
    CPPUNIT_ASSERT(0 == charValue.GetCharacter()->GetByte3());
    CPPUNIT_ASSERT(3 == charValue.GetCharacter()->GetSize());

    charValue = Value::MakeCharacter(0xF0, 0x90, 0x8D, 0x88);
    CPPUNIT_ASSERT(VALUE_OBJECT == charValue.GetType());
    CPPUNIT_ASSERT(0xF0 == charValue.GetCharacter()->GetByte0());
    CPPUNIT_ASSERT(0x90 == charValue.GetCharacter()->GetByte1());
    CPPUNIT_ASSERT(0x8D == charValue.GetCharacter()->GetByte2());
    CPPUNIT_ASSERT(0x88 == charValue.GetCharacter()->GetByte3());
    CPPUNIT_ASSERT(4 == charValue.GetCharacter()->GetSize());
}
