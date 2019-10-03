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
#include "ast/ReferenceExpression.hh"
#include "ast/ArrayAccessExpression.hh"
#include "ast/LiteralExpression.hh"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(PrimaryExpression)

    BOOST_AUTO_TEST_CASE(SimpleReferenceExpression1) {
        auto source = "name;";
        ParserDriver driver(source, "test.hoo");
        auto compilation_unit = driver.BuildModule();
        BOOST_CHECK(compilation_unit->Success());
        auto unit = compilation_unit->GetUnit();
        BOOST_CHECK_NE(nullptr, unit);
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto firstItem = *(items.begin());
        BOOST_CHECK_EQUAL(firstItem->GetUnitItemType(), UNIT_ITEM_STATEMENT);
        auto statement = (Statement*) firstItem;
        BOOST_CHECK_NE(nullptr, statement);
        BOOST_CHECK_EQUAL(statement->GetStatementType(), STMT_EXPRESSION);
        auto expression = ((ExpressionStatement*) statement)->GetExpression();
        BOOST_CHECK_NE(nullptr, expression);
        BOOST_CHECK_EQUAL(expression->GetExpressionType(), EXPRESSION_REFERENCE);
        auto reference_expr = (ReferenceExpression*) expression;
        BOOST_CHECK_NE(nullptr, reference_expr);
        BOOST_CHECK_EQUAL("name", reference_expr->GetName());
        BOOST_CHECK_EQUAL(nullptr, reference_expr->GetParent());
    }

    BOOST_AUTO_TEST_CASE(NestedReferenceExpression1) {
        auto source = "person.name;";
        ParserDriver driver(source, "test.hoo");
        auto compilation_unit = driver.BuildModule();
        BOOST_CHECK(compilation_unit->Success());
        auto unit = compilation_unit->GetUnit();
        BOOST_CHECK_NE(nullptr, unit);
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto firstItem = *(items.begin());
        BOOST_CHECK_EQUAL(firstItem->GetUnitItemType(), UNIT_ITEM_STATEMENT);
        auto statement = (Statement*) firstItem;
        BOOST_CHECK_NE(nullptr, statement);
        BOOST_CHECK_EQUAL(statement->GetStatementType(), STMT_EXPRESSION);
        auto expression = ((ExpressionStatement*) statement)->GetExpression();
        BOOST_CHECK_NE(nullptr, expression);
        BOOST_CHECK_EQUAL(expression->GetExpressionType(), EXPRESSION_REFERENCE);
        auto reference_expr = (ReferenceExpression*) expression;
        BOOST_CHECK_NE(nullptr, reference_expr);
        BOOST_CHECK_EQUAL("name", reference_expr->GetName());
        BOOST_CHECK_NE(nullptr, reference_expr->GetParent());
        BOOST_CHECK_EQUAL("person", reference_expr->GetParent()->GetName());
    }

    BOOST_AUTO_TEST_CASE(NestedReferenceExpression2) {
        auto source = "home.person.name;";
        ParserDriver driver(source, "test.hoo");
        auto compilation_unit = driver.BuildModule();
        BOOST_CHECK(compilation_unit->Success());
        auto unit = compilation_unit->GetUnit();
        BOOST_CHECK_NE(nullptr, unit);
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto firstItem = *(items.begin());
        BOOST_CHECK_EQUAL(firstItem->GetUnitItemType(), UNIT_ITEM_STATEMENT);
        auto statement = (Statement*) firstItem;
        BOOST_CHECK_NE(nullptr, statement);
        BOOST_CHECK_EQUAL(statement->GetStatementType(), STMT_EXPRESSION);
        auto expression = ((ExpressionStatement*) statement)->GetExpression();
        BOOST_CHECK_NE(nullptr, expression);
        BOOST_CHECK_EQUAL(expression->GetExpressionType(), EXPRESSION_REFERENCE);
        auto reference_expr = (ReferenceExpression*) expression;
        BOOST_CHECK_NE(nullptr, reference_expr);
        BOOST_CHECK_EQUAL("name", reference_expr->GetName());
        BOOST_CHECK_NE(nullptr, reference_expr->GetParent());
        BOOST_CHECK_EQUAL("person", reference_expr->GetParent()->GetName());
        auto home = reference_expr->GetParent()
                ->GetParent();
        BOOST_CHECK_NE(nullptr, home);
        BOOST_CHECK_EQUAL("home", home->GetName());
        BOOST_CHECK_EQUAL(nullptr, home->GetParent());
    }

    BOOST_AUTO_TEST_CASE(ArrayAccessExpression1) {
        auto source = "persons[0];";
        ParserDriver driver(source, "test.hoo");
        auto compilation_unit = driver.BuildModule();
        BOOST_CHECK(compilation_unit->Success());
        auto unit = compilation_unit->GetUnit();
        BOOST_CHECK_NE(nullptr, unit);
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto firstItem = *(items.begin());
        BOOST_CHECK_EQUAL(firstItem->GetUnitItemType(), UNIT_ITEM_STATEMENT);
        auto statement = (Statement*) firstItem;
        BOOST_CHECK_NE(nullptr, statement);
        BOOST_CHECK_EQUAL(statement->GetStatementType(), STMT_EXPRESSION);
        auto expression = ((ExpressionStatement*) statement)->GetExpression();
        BOOST_CHECK_NE(nullptr, expression);
        BOOST_CHECK_EQUAL(expression->GetExpressionType(), EXPRESSION_ARRAY);
        auto array_expr = (ArrayAccessExpression*) expression;
        BOOST_CHECK_NE(nullptr, array_expr);
        auto container = array_expr->GetContainer();
        BOOST_CHECK_EQUAL(container->GetExpressionType(), EXPRESSION_REFERENCE);
        auto persons = (ReferenceExpression*) container;
        BOOST_CHECK_NE(nullptr, persons);
        BOOST_CHECK_EQUAL("persons", persons->GetName());
        auto index = array_expr->GetIndex();
        BOOST_CHECK_NE(nullptr, index);
        BOOST_CHECK_EQUAL(index->GetExpressionType(), EXPRESSION_LITERAL);
        auto literal = (LiteralExpression*) index;
        BOOST_CHECK_EQUAL(literal->GetLiteralType(), LITERAL_INTEGER);
        BOOST_CHECK_EQUAL(literal->GetValue(), "0");
    }

    BOOST_AUTO_TEST_CASE(ArrayAccessExpression2) {
        auto source = "home.persons[23];";
        ParserDriver driver(source, "test.hoo");
        auto compilation_unit = driver.BuildModule();
        BOOST_CHECK(compilation_unit->Success());
        auto unit = compilation_unit->GetUnit();
        BOOST_CHECK_NE(nullptr, unit);
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto firstItem = *(items.begin());
        BOOST_CHECK_EQUAL(firstItem->GetUnitItemType(), UNIT_ITEM_STATEMENT);
        auto statement = (Statement*) firstItem;
        BOOST_CHECK_NE(nullptr, statement);
        BOOST_CHECK_EQUAL(statement->GetStatementType(), STMT_EXPRESSION);
        auto expression = ((ExpressionStatement*) statement)->GetExpression();
        BOOST_CHECK_NE(nullptr, expression);
        BOOST_CHECK_EQUAL(expression->GetExpressionType(), EXPRESSION_ARRAY);
        auto array_expr = (ArrayAccessExpression*) expression;
        BOOST_CHECK_NE(nullptr, array_expr);
        auto container = array_expr->GetContainer();
        auto index = array_expr->GetIndex();
        BOOST_CHECK_NE(nullptr, index);
        BOOST_CHECK_EQUAL(index->GetExpressionType(), EXPRESSION_LITERAL);
        auto literal = (LiteralExpression*) index;
        BOOST_CHECK_EQUAL(literal->GetLiteralType(), LITERAL_INTEGER);
        BOOST_CHECK_EQUAL(literal->GetValue(), "23");

        BOOST_CHECK_EQUAL(container->GetExpressionType(), EXPRESSION_REFERENCE);
        auto persons = (ReferenceExpression*) container;
        BOOST_CHECK_NE(nullptr, persons);
        BOOST_CHECK_EQUAL("persons", persons->GetName());
        auto home = persons->GetParent();
        BOOST_CHECK_NE(nullptr, home);
        BOOST_CHECK_EQUAL("home", home->GetName());
    }

BOOST_AUTO_TEST_SUITE_END()