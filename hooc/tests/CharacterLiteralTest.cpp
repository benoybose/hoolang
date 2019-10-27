/*
 * Copyright 2019 Benoy Bose
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

#include "compiler/ParserDriver.hh"
#include "ast/UnitItem.hh"
#include "ast/Statement.hh"
#include "ast/LiteralExpression.hh"

#include <boost/test/unit_test.hpp>
#include <ast/ExpressionStatement.hh>


using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(CharacterLiteralTest)

    BOOST_AUTO_TEST_CASE(TEST01) {
        auto source = "'a';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK("'a'" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(TEST02) {
        auto source = "'Z';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK("'Z'" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(TEST03) {
        auto source = "'\\r';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK("'\\r'" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(TEST04) {
        auto source = "'\\n';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK("'\\n'" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(TEST05) {
        auto source = "'\n';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        BOOST_CHECK(unit->GetItems().empty());
    }

    BOOST_AUTO_TEST_CASE(TEST06) {
        auto source = "'\r';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        BOOST_CHECK(unit->GetItems().empty());
    }

    BOOST_AUTO_TEST_CASE(TEST07) {
        auto source = "'$';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK("'$'" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(CharacterLiteral_8) {
        auto source = "'3';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK("'3'" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(CharacterLiteral_9) {
        auto source = "'ab';";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        auto item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != item);
        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
        auto statement = (ExpressionStatement *) item;
        BOOST_CHECK(nullptr != statement);
        auto expression = (LiteralExpression *) statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_CHARACTER);
        BOOST_CHECK(0 == expression->GetValue().compare("'ab'"));
    }

BOOST_AUTO_TEST_SUITE_END()