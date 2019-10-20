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

#include <boost/test/unit_test.hpp>
#include <ast/ExpressionStatement.hh>

#include "compiler/ParserDriver.hh"
#include "ast/UnitItem.hh"
#include "ast/Statement.hh"
#include "ast/LiteralExpression.hh"

using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(DecimalLiteral)

    BOOST_AUTO_TEST_CASE(DecimalLiteral_1) {
        auto source = "2.0;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("2.0" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_2) {
        auto source = "3.14;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("3.14" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_3) {
        auto source = "314.;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("314." == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_4) {
        auto source = ".314;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK(".314" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_5) {
        auto source = "+2.0;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("+2.0" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_6) {
        auto source = "+3.14;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("+3.14" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_7) {
        auto source = "+314.;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("+314." == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_8) {
        auto source = "+.314;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("+.314" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_9) {
        auto source = "-2.0;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("-2.0" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_10) {
        auto source = "-3.14;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("-3.14" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_11) {
        auto source = "-314.;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("-314." == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_12) {
        auto source = "-.314;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("-.314" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_13) {
        auto source = "3.6e34;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("3.6e34" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_14) {
        auto source = "3.6E34;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("3.6E34" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_15) {
        auto source = "3.6e-34;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("3.6e-34" == expression->GetValue());
    }

    BOOST_AUTO_TEST_CASE(DecimalLiteral_16) {
        auto source = "3.6E+34;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("3.6E+34" == expression->GetValue());
    }

    // todo: HexadecimalFloatingConstant need to be tested
    BOOST_AUTO_TEST_CASE(DecimalLiteral_Hexa1) {
        auto source = "0XAB089.AB089;";
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
        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
        BOOST_CHECK("0XAB089.AB089" == expression->GetValue());
    }

//    BOOST_AUTO_TEST_CASE(DecimalLiteral_Hexa2) {
//        auto source = "0XAB089.0p0;";
//        ParserDriver driver(source, "test.hoo");
//        auto module = driver.BuildModule();
//        BOOST_CHECK(module->Success());
//        auto unit = module->GetUnit();
//        BOOST_CHECK(nullptr != unit);
//        auto item = *(unit->GetItems().begin());
//        BOOST_CHECK(nullptr != item);
//        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
//        auto statement = (ExpressionStatement *) item;
//        BOOST_CHECK(nullptr != statement);
//        auto expression = (LiteralExpression *) statement->GetExpression();
//        BOOST_CHECK(nullptr != expression);
//        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
//        BOOST_CHECK("0XAB089.p0" == expression->GetValue());
//    }

//    BOOST_AUTO_TEST_CASE(DecimalLiteral_Hexa3) {
//        auto source = ".0XAB089p0;";
//        ParserDriver driver(source, "test.hoo");
//        auto module = driver.BuildModule();
//        BOOST_CHECK(module->Success());
//        auto unit = module->GetUnit();
//        BOOST_CHECK(nullptr != unit);
//        auto item = *(unit->GetItems().begin());
//        BOOST_CHECK(nullptr != item);
//        BOOST_CHECK(item->GetUnitItemType() == UNIT_ITEM_STATEMENT);
//        auto statement = (ExpressionStatement *) item;
//        BOOST_CHECK(nullptr != statement);
//        auto expression = (LiteralExpression *) statement->GetExpression();
//        BOOST_CHECK(nullptr != expression);
//        BOOST_CHECK(expression->GetLiteralType() == LITERAL_DOUBLE);
//        BOOST_CHECK(".0XAB089" == expression->GetValue());
//    }

BOOST_AUTO_TEST_SUITE_END()