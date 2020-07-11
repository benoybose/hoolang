#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>

using namespace hoo::parser;

class BasicClassDefinitionTest : public hoo::test::TestUnit
{
public:
    BasicClassDefinitionTest() {
        RegisterTestCase("EmptyClassDefinitionTest", &BasicClassDefinitionTest::EmptyClassDefinitionTest);
    }

public:
    void EmptyClassDefinitionTest()
    {
        const auto source = "class Human {}";
        ParserDriver driver(source);
    }
};

HOO_TEST_CASE(BasicClassDefinitionTest)
