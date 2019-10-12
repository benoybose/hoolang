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
#include "ast/Unit.hh"
#include "ast/Statement.hh"
#include "ast/Declaration.hh"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <ast/LiteralExpression.hh>
#include <ast/ExpressionStatement.hh>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(IntegerLiteral)

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_1) {
        auto source = "362880;";
        ParserDriver driver(source, "test.hoo");

        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        BOOST_CHECK(nullptr != module);
        auto unit = module->GetUnit();
        BOOST_CHECK(nullptr != unit);
        BOOST_CHECK(1 == unit->GetItems().size());

        auto unit_item = *(unit->GetItems().begin());
        BOOST_CHECK(nullptr != unit_item);
        BOOST_CHECK(UNIT_ITEM_STATEMENT == unit_item->GetUnitItemType());

        auto statement = (Statement *) unit_item;
        BOOST_CHECK(nullptr != statement);
        BOOST_CHECK(STMT_EXPRESSION == statement->GetStatementType());

        auto expression_statement = (ExpressionStatement *) statement;
        BOOST_CHECK(nullptr != expression_statement);
        auto expression = expression_statement->GetExpression();
        BOOST_CHECK(nullptr != expression);
        BOOST_CHECK(EXPRESSION_LITERAL == expression->GetExpressionType());
        auto literal_expression = (LiteralExpression *) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("362880" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_2) {
        auto source = "+362880;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("+362880" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_3) {
        auto source = "-362880;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("-362880" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_4) {
        auto source = "03620;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("03620" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_5) {
        auto source = "036208;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(!module->Success());
        auto errors = module->GetErrors();
        BOOST_CHECK(1 == errors.size());
        auto first_error = *(errors.begin());
        BOOST_CHECK(1 == first_error->GetLineNumber());
        BOOST_CHECK(0 == first_error->GetCharacterPosition());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_6) {
        auto source = "0xAB089;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("0xAB089" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_7) {
        auto source = "0XAB089;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("0XAB089" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_8) {
        auto source = "0xAB08K;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(!module->Success());
        auto errors = module->GetErrors();
        BOOST_CHECK(1 == errors.size());
        auto first_error = *(errors.begin());
        BOOST_CHECK(1 == first_error->GetLineNumber());
        BOOST_CHECK(6 == first_error->GetCharacterPosition());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_9) {
        auto source = "0b101010;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("0b101010" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_10) {
        auto source = "0B101010;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(0 == module->GetErrors().size());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        auto first_item = *(unit_items.begin());
        auto statement = (Statement*) first_item;
        auto expression_statement = (ExpressionStatement*) statement;
        auto expression = expression_statement->GetExpression();
        auto literal_expression = (LiteralExpression*) expression;
        BOOST_CHECK(nullptr != literal_expression);
        BOOST_CHECK(LITERAL_INTEGER == literal_expression->GetLiteralType());
        BOOST_CHECK("0B101010" == literal_expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(IntegerLiteralExpression_11) {
        auto source = "0b111203;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(!module->Success());
        auto errors = module->GetErrors();
        BOOST_CHECK(1 == errors.size());
        auto first_error = *(errors.begin());
        BOOST_CHECK(1 == first_error->GetLineNumber());
        BOOST_CHECK(5 == first_error->GetCharacterPosition());
    }

BOOST_AUTO_TEST_SUITE_END()