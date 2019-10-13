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
#include <ast/ReturnStatement.hh>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(ReturnStatementTest)

    BOOST_AUTO_TEST_CASE(ReturnStatement1) {
        std::string source = "return 102;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_RETURN, stmt->GetStatementType());
        auto stmt_return = (ReturnStatement *) stmt;
        BOOST_CHECK_LITERAL_EXPRESSION(stmt_return->GetExpression(), LITERAL_INTEGER, "102");
        delete module;
    }

    BOOST_AUTO_TEST_CASE(ReturnStatement2) {
        std::string source = "return name;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_RETURN, stmt->GetStatementType());
        auto stmt_return = (ReturnStatement *) stmt;
        BOOST_CHECK_REFERENCE_EXPRESSION(stmt_return->GetExpression(), "name");
        delete module;
    }

    BOOST_AUTO_TEST_CASE(ReturnStatement3) {
        std::string source = "return person.name;";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        BOOST_CHECK(module->Success());
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        BOOST_CHECK_EQUAL(1, items.size());
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_RETURN, stmt->GetStatementType());
        auto stmt_return = (ReturnStatement *) stmt;
        auto expr_return = stmt_return->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_REFERENCE, expr_return->GetExpressionType());
        auto name = (ReferenceExpression *) expr_return;
        BOOST_CHECK_EQUAL("name", name->GetName());
        auto person = (ReferenceExpression *) name->GetParent();
        BOOST_CHECK_EQUAL("person", person->GetName());
        BOOST_CHECK_EQUAL(nullptr, person->GetParent());
        delete module;
    }

BOOST_AUTO_TEST_SUITE_END()