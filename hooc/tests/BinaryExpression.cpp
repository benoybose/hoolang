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
#include "ast/BinaryExpression.hh"
#include "HoocTestHelper.hh"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(BinaryExpressionTest)

    BOOST_AUTO_TEST_CASE(BinaryExpression1) {
        const std::string source = "2 + 3;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        auto unit_items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, unit_items.size());
        auto unit_item = *(unit_items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, unit_item->GetUnitItemType());
        auto stmt = (Statement *) unit_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto expr = ((ExpressionStatement *) unit_item)->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_BINARY, expr->GetExpressionType());
        auto binary_expr = (BinaryExpression *) expr;
        auto lvalue = binary_expr->GetLeftExpression();
        auto rvalue = binary_expr->GetRightExpression();
        auto opr = binary_expr->GetOperator();
        BOOST_CHECK_LITERAL_EXPRESSION(lvalue, LITERAL_INTEGER, "2");
        BOOST_CHECK_LITERAL_EXPRESSION(rvalue, LITERAL_INTEGER, "3");
        BOOST_CHECK_EQUAL(OPERATOR_ADD, opr->GetOperatorType());
    }

BOOST_AUTO_TEST_SUITE_END()