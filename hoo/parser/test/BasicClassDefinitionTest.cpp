#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>
#include <hoo/parser/ParseException.hh>
#include <hoo/ast/AST.hh>

#include <memory>

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
        auto unit = DoesNotThrowAndReturn<ParseException,
                                          std::shared_ptr<hoo::ast::Unit>>([source]() -> std::shared_ptr<hoo::ast::Unit> {
            ParserDriver driver(source);
            auto unit = driver.Build();
            return unit;
        });

        NotNull(unit);
        if (!unit)
        {
            return;
        }

        auto unit_items = unit->GetItems();
        Count<>(unit_items, 1);
        auto single_item = *unit_items.begin();
        auto classDefinition = IsA<ClassDefinition, UnitItem>(single_item);
        if (!classDefinition)
        {
            return;
        }
        StringEqual(classDefinition->GetClassName(), "Human");
        False(classDefinition->HasBaseEntities());
        True(classDefinition->IsEmpty());
    }
};

HOO_TEST_CASE(BasicClassDefinitionTest)
