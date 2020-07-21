/*
 * Copyright 2020 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <hoo/test/HooTest.hh>
#include <hoo/parser/ParserDriver.hh>
#include <hoo/parser/ParseException.hh>
#include <hoo/parser/SyntaxError.hh>
#include <hoo/ast/AST.hh>

#include <memory>

using namespace hoo::test;
using namespace hoo::parser;
using namespace hoo::ast;

class BasicClassDefinitionTest : public TestUnit
{
public:
    BasicClassDefinitionTest()
    {
        RegisterTestCase("EmptyClassDefinitionTest",
                         &BasicClassDefinitionTest::EmptyClassDefinitionTest);
        RegisterTestCase("DerivedClassTest",
                         &BasicClassDefinitionTest::DerivedClassTest);
        RegisterTestCase("MultipleBaseEntitiesTest",
                         &BasicClassDefinitionTest::MultipleBaseEntitiesTest);
        RegisterTestCase("InvalidClassDefTest",
                         &BasicClassDefinitionTest::InvalidClassDefTest);
    }

private:
    std::shared_ptr<ClassDefinition> BuildSingleUnitClassDef(const std::string &source)
    {
        auto unit = DoesNotThrowAndReturn<ParseException,
                                          std::shared_ptr<hoo::ast::Unit>>([source]()
                                                                               -> std::shared_ptr<hoo::ast::Unit> {
            ParserDriver driver(source);
            auto unit = driver.Build();
            return unit;
        });

        NotNull(unit);
        if (!unit)
        {
            return std::shared_ptr<ClassDefinition>(nullptr);
        }

        auto unit_items = unit->GetItems();
        Count<>(unit_items, 1);
        auto single_item = *unit_items.begin();
        auto classDefinition = IsA<ClassDefinition, UnitItem>(single_item);
        return classDefinition;
    }

public:
    void EmptyClassDefinitionTest()
    {
        const auto source = "class Human {}";
        auto class_def = BuildSingleUnitClassDef(source);
        if (!class_def)
        {
            return;
        }
        StringEqual(class_def->GetClassName(), "Human");
        False(class_def->HasBaseEntities());
        True(class_def->IsEmpty());
    }

    void DerivedClassTest()
    {
        const auto source = "class Male: Human {}";
        auto class_def = BuildSingleUnitClassDef(source);
        if (!class_def)
        {
            return;
        }
        const auto class_name = class_def->GetClassName();
        StringEqual(class_name, "Male");
        True(class_def->HasBaseEntities());
        auto base_entities = class_def->GetBaseEntities();
        Count<>(base_entities, 1);
        Equal(base_entities, {"Human"});
        True(class_def->IsEmpty());
    }

    void MultipleBaseEntitiesTest()
    {
        const auto source = "class Color: Red, Green, Blue, Alpha {}";
        auto class_def = BuildSingleUnitClassDef(source);
        if (!class_def)
        {
            return;
        }
        const auto class_name = class_def->GetClassName();
        StringEqual(class_name, "Color");
        True(class_def->HasBaseEntities());
        auto base_entities = class_def->GetBaseEntities();
        Count<>(base_entities, 4);
        Equal(base_entities, {"Red", "Green", "Blue", "Alpha"});
        True(class_def->IsEmpty());
    }

    void InvalidClassDefTest()
    {
        try
        {
            const auto source = "class #ClassName {}";
            ParserDriver driver(source);
            auto unit = driver.Build();
        }
        catch (ParseException& ex)
        {
            std::cout << "Parse exception is caught";
        }
    }
};

HOO_TEST_CASE(BasicClassDefinitionTest)
