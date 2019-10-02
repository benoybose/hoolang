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

BOOST_AUTO_TEST_SUITE_END()