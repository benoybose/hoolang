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

#include "ParserTestHelper.hh"

#include <hoo/ast/AST.hh>
#include <hoo/parser/ParserDriver.hh>

#include <memory>
#include <list>

using namespace hoo::ast;
using namespace hoo::parser;

std::shared_ptr<Unit> ParserTestHelper::BuildUnit(const std::string &source)
{
    ParserDriver driver(source);
    auto unit = driver.Build();
    return unit;
}

std::shared_ptr<ClassDefinition> ParserTestHelper::GetClassByName(std::shared_ptr<Unit> unit,
                                                                  const std::string &expected_class_name)
{
    auto unit_items = unit->GetItems();
    for (auto unit_item : unit_items)
    {
        const auto unit_item_type = unit_item->GetUnitItemType();
        if (UNIT_ITEM_DEFINITION != unit_item_type)
        {
            continue;
        }

        auto definition = std::static_pointer_cast<Definition>(unit_item);
        const auto definition_type = definition->GetDefinitionType();
        if (DEFINITION_CLASS != definition_type)
        {
            continue;
        }

        auto class_definition = std::static_pointer_cast<ClassDefinition>(definition);
        const auto original_class_name = class_definition->GetClassName();
        if (original_class_name == expected_class_name)
        {
            return class_definition;
        }
    }
    return std::shared_ptr<ClassDefinition>(nullptr);
}

std::list<std::shared_ptr<FunctionDefinition>>
ParserTestHelper::GetFunctionsByName(std::shared_ptr<ClassDefinition> class_definition,
                                     const std::string &function_name)
{
    std::list<std::shared_ptr<FunctionDefinition>> functions;
    auto class_body = class_definition->GetBody();
    auto items = class_body->GetItems();
    for(auto item: items)
    {
        const auto item_type = item->GetType();
        if (CLSBODY_DEFINITION != item_type)
        {
            continue;
        }

        auto definition = item->GetDefinition();
        const auto definition_type = definition->GetDefinitionType();
        if (DEFINITION_FUNCTION != definition_type)
        {
            continue;
        }

        auto function_definition = std::static_pointer_cast<FunctionDefinition>(definition);
        functions.push_back(function_definition);
    }
    return functions;
}