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

#include <iostream>
#include "HooLexer.h"

#include <hoo/ast/AST.hh>
#include <hoo/parser/visitors/VisitorHelper.hh>
#include <hoo/parser/ErrorListener.hh>
#include <hoo/parser/visitors/UnitVisitor.hh>
#include <hoo/parser/visitors/DefinitionVisitor.hh>
#include <hoo/parser/visitors/StatementVisitor.hh>

#include <list>
#include <string>
#include <utility>
#include <regex>
#include <memory>

using namespace hoo::ast;
using namespace antlrcpp;
using namespace hoo::parser;

UnitVisitor::UnitVisitor(ErrorListener *error_listener)
    : _error_listener(error_listener)
{
}

Any UnitVisitor::visitUnit(HooParser::UnitContext *ctx)
{
    auto items = ctx->unitItem();
    std::list<std::shared_ptr<UnitItem>> unit_items;
    for (auto item : items)
    {
        auto unit_item = this->visit(item).as<UnitItem *>();
        if (nullptr != unit_item)
        {
            unit_items.push_back(std::shared_ptr<UnitItem>(unit_item));
        }
        else
        {
            _error_listener->Add(item, "Invalid source.");
        }
    }

    auto unit = new Unit(unit_items);
    return Any(unit);
}

Any UnitVisitor::visitUnitItem(HooParser::UnitItemContext *ctx)
{
    auto definition_context = ctx->defenition();
    UnitItem *unit_item = nullptr;

    if (nullptr != definition_context)
    {
        DefinitionVisitor visitor(_error_listener);
        auto definition = visitor.visit(definition_context)
                              .as<Definition *>();
        unit_item = (UnitItem *)definition;
    }
    else
    {
        auto statement_context = ctx->statement();
        if (nullptr != statement_context)
        {
            StatementVisitor visitor(_error_listener);
            auto statement = visitor.visit(statement_context)
                                 .as<Statement *>();
            unit_item = (UnitItem *)statement;
        }
    }

    return Any(unit_item);
}
