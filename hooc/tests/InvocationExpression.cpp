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
#include "ast/InvokeExpression.hh"
#include "ast/ArrayAccessExpression.hh"
#include "ast/LiteralExpression.hh"

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(InvocationExpression)

    BOOST_AUTO_TEST_CASE(SimpleInvocationExpression1) {
        auto source = "foo();";
        ParserDriver driver(source, "test.hoo");
        auto compilation_unit = driver.BuildModule();
        auto unit = compilation_unit->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement*) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement*) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression*) expr;
        auto foo = invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL(foo->GetExpressionType(), EXPRESSION_REFERENCE);
        BOOST_CHECK_EQUAL("foo", ((ReferenceExpression*) foo)->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(0, arguments.size());
    }

BOOST_AUTO_TEST_SUITE_END()