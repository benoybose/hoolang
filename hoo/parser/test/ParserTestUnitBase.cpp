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

#include "ParserTestUnitBase.hh"
#include <hoo/parser/ParseException.hh>
#include <hoo/parser/ParserDriver.hh>

#include <memory>

using namespace hoo::ast;
using namespace hoo::parser;

std::shared_ptr<Unit> ParserTestUnitBase::ParseUnit(const std::string &source)
{
    auto unit = DoesNotThrowAndReturn<ParseException,
                                      std::shared_ptr<hoo::ast::Unit>>([source]()
                                                                           -> std::shared_ptr<hoo::ast::Unit> {
        ParserDriver driver(source, true);
        auto unit = driver.Build();
        return unit;
    });

    NotNull(unit);
    return unit;
}

std::shared_ptr<ClassDefinition> ParserTestUnitBase::GetClassByName(std::shared_ptr<Unit> unit,
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
ParserTestUnitBase::GetFunctionsByName(std::shared_ptr<ClassDefinition> class_definition,
                                       const std::string &function_name)
{
    std::list<std::shared_ptr<FunctionDefinition>> functions;
    auto class_body = class_definition->GetBody();
    auto items = class_body->GetItems();
    for (auto item : items)
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

void ParserTestUnitBase::VerifyType(std::shared_ptr<TypeSpecification> type,
                                    BasicDataTypeType expected_basic_data_type)
{
    NotNull(type);
    auto type_spec_type = type->GetType();
    Equal(type_spec_type, TYPE_SPEC_BASIC);
    auto basic_data_type = std::static_pointer_cast<BasicTypeSpec>(type);
    NotNull(basic_data_type);
    auto data_type = basic_data_type->GetDataType();
    Equal(data_type, expected_basic_data_type);
}

std::shared_ptr<CompoundStatement>
ParserTestUnitBase::AsCompoundStatement(std::shared_ptr<Statement> statement)
{
    NotNull(statement);
    const auto statement_type = statement->GetStatementType();
    Equal(statement_type, STMT_COMPOUND);
    auto compound_statement = std::static_pointer_cast<CompoundStatement>(statement);
    NotNull(compound_statement);
    return compound_statement;
}

std::shared_ptr<FunctionDefinition> 
ParserTestUnitBase::GetClassMethod(const std::string source,
                                                   const std::string &expcted_class_name,
                                                   const std::string &expected_func_name)
{
    auto unit = DoesNotThrowAndReturn<ParseException,
                                      std::shared_ptr<hoo::ast::Unit>>([this, source]()
                                                                           -> std::shared_ptr<hoo::ast::Unit> {
        auto unit = ParseUnit(source);
        return unit;
    });
    NotNull(unit);

    auto class_definition = GetClassByName(unit, expcted_class_name);
    NotNull(class_definition);

    auto function_definitions = GetFunctionsByName(class_definition, expected_func_name);
    NotEmpty(function_definitions);
    auto func_def = *function_definitions.begin();
    return func_def;
}