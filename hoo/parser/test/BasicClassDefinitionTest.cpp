#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>
#include <hoo/parser/ParseException.hh>
#include <hoo/ast/AST.hh>

using namespace hoo::parser;
using namespace hoo::ast;

class BasicClassDefinitionTest : public hoo::test::TestUnit
{
public:
    BasicClassDefinitionTest()
    {
        RegisterTestCase("EmptyClassDefinitionTest",
                         &BasicClassDefinitionTest::EmptyClassDefinitionTest);
    }

public:
    void EmptyClassDefinitionTest()
    {
        const auto source = "class Human {}";
        auto unit = DoesNotThrowAndReturn<ParseException, const Unit *>([source]() -> const Unit * {
            ParserDriver driver(source);
            return driver.BuildModule();
        });
        NotNull(unit);
        auto unit_items = unit->GetItems();
        Count<UnitItem *>(unit_items, 1);
        auto single_item = *unit_items.begin();
        IsA<ClassDefinition*>(single_item);
    }
};

HOO_TEST_CASE(BasicClassDefinitionTest)
