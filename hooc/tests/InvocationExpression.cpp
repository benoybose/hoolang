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
#include <ast/ExpressionStatement.hh>

using namespace std;
using namespace hooc;
using namespace hooc::compiler;
using namespace hooc::ast;

BOOST_AUTO_TEST_SUITE(InvocationExpression)

    BOOST_AUTO_TEST_CASE(SimpleInvocationExpression1) {
        auto source = "foo();";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        auto foo = invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL(foo->GetExpressionType(), EXPRESSION_REFERENCE);
        BOOST_CHECK_EQUAL("foo", ((ReferenceExpression *) foo)->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(0, arguments.size());
    }

    BOOST_AUTO_TEST_CASE(SimpleInvocationExpression2) {
        auto source = "foo.bar();";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        auto bar = invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL(bar->GetExpressionType(), EXPRESSION_REFERENCE);
        BOOST_CHECK_EQUAL("bar", ((ReferenceExpression *) bar)->GetName());
        BOOST_CHECK_EQUAL("foo", ((ReferenceExpression *) ((ReferenceExpression *) bar)->GetParent())->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(0, arguments.size());
    }

    BOOST_AUTO_TEST_CASE(ParameteredInvocationExpression1) {
        auto source = "console.print(\"Hello World!\");";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        auto bar = invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL(bar->GetExpressionType(), EXPRESSION_REFERENCE);
        BOOST_CHECK_EQUAL("print", ((ReferenceExpression *) bar)->GetName());
        BOOST_CHECK_EQUAL("console", ((ReferenceExpression *) ((ReferenceExpression *) bar)->GetParent())->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(1, arguments.size());
        auto arg1 = *(arguments.begin());
        BOOST_CHECK_EQUAL(EXPRESSION_LITERAL, arg1->GetExpressionType());
        auto hello_world = (LiteralExpression *) arg1;
        BOOST_CHECK_EQUAL(LITERAL_STRING, hello_world->GetLiteralType());
        BOOST_CHECK_EQUAL("\"Hello World!\"", hello_world->GetValue());
    }

    BOOST_AUTO_TEST_CASE(ParameteredInvocationExpression2) {
        auto source = "bar.foo(362880, 3.14678, true, 'B');";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        BOOST_CHECK_EQUAL(EXPRESSION_REFERENCE, invoke_expr->GetReceiver()->GetExpressionType());
        auto foo = (ReferenceExpression *) invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL("foo", foo->GetName());
        BOOST_CHECK_EQUAL(EXPRESSION_REFERENCE, foo->GetParent()->GetExpressionType());
        auto bar = (ReferenceExpression *) foo->GetParent();
        BOOST_CHECK_EQUAL("bar", bar->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(4, arguments.size());
        auto iterator = arguments.begin();

        auto arg1 = *(iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_LITERAL, arg1->GetExpressionType());
        auto arg_int = (LiteralExpression *) arg1;
        BOOST_CHECK_EQUAL(LITERAL_INTEGER, arg_int->GetLiteralType());
        BOOST_CHECK_EQUAL("362880", arg_int->GetValue());

        auto arg2 = *(++iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_LITERAL, arg1->GetExpressionType());
        auto arg_double = (LiteralExpression *) arg2;
        BOOST_CHECK_EQUAL(LITERAL_DOUBLE, arg_double->GetLiteralType());
        BOOST_CHECK_EQUAL("3.14678", arg_double->GetValue());

        auto arg3 = *(++iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_LITERAL, arg3->GetExpressionType());
        auto arg_bool = (LiteralExpression *) arg3;
        BOOST_CHECK_EQUAL(LITERAL_BOOLEAN, arg_bool->GetLiteralType());
        BOOST_CHECK_EQUAL("true", arg_bool->GetValue());

        auto arg4 = *(++iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_LITERAL, arg4->GetExpressionType());
        auto arg_char = (LiteralExpression *) arg4;
        BOOST_CHECK_EQUAL(LITERAL_CHARACTER, arg_char->GetLiteralType());
        BOOST_CHECK_EQUAL("'B'", arg_char->GetValue());
    }

    BOOST_AUTO_TEST_CASE(ParameteredInvocationExpression3) {
        auto source = "bar.foo(id, person.name);";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        BOOST_CHECK_EQUAL(invoke_expr->GetReceiver()->GetExpressionType(), EXPRESSION_REFERENCE);
        auto foo = (ReferenceExpression *) invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL("foo", foo->GetName());
        BOOST_CHECK_EQUAL(foo->GetParent()->GetExpressionType(), EXPRESSION_REFERENCE);
        auto bar = (ReferenceExpression *) foo->GetParent();
        BOOST_CHECK_EQUAL("bar", bar->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(2, arguments.size());
        auto iterator = arguments.begin();

        auto arg1 = *(iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_REFERENCE, arg1->GetExpressionType());
        auto arg_id = (ReferenceExpression *) arg1;
        BOOST_CHECK_EQUAL("id", arg_id->GetName());

        auto arg2 = *(++iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_REFERENCE, arg1->GetExpressionType());
        auto arg_name = (ReferenceExpression *) arg2;
        BOOST_CHECK_EQUAL("name", arg_name->GetName());
        BOOST_CHECK_EQUAL("person", ((ReferenceExpression *) arg_name->GetParent())->GetName());
    }

    BOOST_AUTO_TEST_CASE(ParameteredInvocationExpression4) {
        auto source = "bar.foo(bar(x, y), foo (a, b));";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        BOOST_CHECK_EQUAL(invoke_expr->GetReceiver()->GetExpressionType(), EXPRESSION_REFERENCE);
        auto foo = (ReferenceExpression *) invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL("foo", foo->GetName());
        BOOST_CHECK_EQUAL(foo->GetParent()->GetExpressionType(), EXPRESSION_REFERENCE);
        auto bar = (ReferenceExpression *) foo->GetParent();
        BOOST_CHECK_EQUAL("bar", bar->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(2, arguments.size());
        auto iterator = arguments.begin();

        auto arg1 = *(iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, arg1->GetExpressionType());
        auto arg_bar = (InvokeExpression *) arg1;
        BOOST_CHECK_EQUAL("bar", ((ReferenceExpression*) arg_bar->GetReceiver())->GetName());
        auto bar_arguments = arg_bar->GetArguments();
        BOOST_CHECK_EQUAL(2, bar_arguments.size());
        auto arg_x = (ReferenceExpression*) *(bar_arguments.begin());
        BOOST_CHECK_EQUAL("x", arg_x->GetName());
        auto arg_y = (ReferenceExpression*) *(++ bar_arguments.begin());
        BOOST_CHECK_EQUAL("y", arg_y->GetName());

        auto arg2 = *(++iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, arg1->GetExpressionType());
        auto arg_foo = (InvokeExpression *) arg2;
        BOOST_CHECK_EQUAL("foo", ((ReferenceExpression*) arg_foo->GetReceiver())->GetName());
        auto foo_arguments = arg_foo->GetArguments();
        BOOST_CHECK_EQUAL(2, foo_arguments.size());
        auto arg_a = (ReferenceExpression*) *(foo_arguments.begin());
        BOOST_CHECK_EQUAL("a", arg_a->GetName());
        auto arg_b = (ReferenceExpression*) *(++ foo_arguments.begin());
        BOOST_CHECK_EQUAL("b", arg_b->GetName());
    }

    BOOST_AUTO_TEST_CASE(ParameteredInvocationExpression5) {
        auto source = "bar.foo(person[\"name\"]);";
        ParserDriver driver(source, "test.hoo");
        auto module = driver.BuildModule();
        auto unit = module->GetUnit();
        auto items = unit->GetItems();
        auto first_item = *(items.begin());
        BOOST_CHECK_EQUAL(UNIT_ITEM_STATEMENT, first_item->GetUnitItemType());
        auto stmt = (Statement *) first_item;
        BOOST_CHECK_EQUAL(STMT_EXPRESSION, stmt->GetStatementType());
        auto stmt_expr = (ExpressionStatement *) stmt;
        auto expr = stmt_expr->GetExpression();
        BOOST_CHECK_EQUAL(EXPRESSION_INVOKE, expr->GetExpressionType());
        auto invoke_expr = (InvokeExpression *) expr;
        BOOST_CHECK_EQUAL(invoke_expr->GetReceiver()->GetExpressionType(), EXPRESSION_REFERENCE);
        auto foo = (ReferenceExpression *) invoke_expr->GetReceiver();
        BOOST_CHECK_EQUAL("foo", foo->GetName());
        BOOST_CHECK_EQUAL(foo->GetParent()->GetExpressionType(), EXPRESSION_REFERENCE);
        auto bar = (ReferenceExpression *) foo->GetParent();
        BOOST_CHECK_EQUAL("bar", bar->GetName());
        auto arguments = invoke_expr->GetArguments();
        BOOST_CHECK_EQUAL(1, arguments.size());
        auto iterator = arguments.begin();

        auto arg1 = *(iterator);
        BOOST_CHECK_EQUAL(EXPRESSION_ARRAY, arg1->GetExpressionType());
        auto array = (ArrayAccessExpression*) arg1;
        auto person = (ReferenceExpression *) array->GetContainer();
        auto name = (LiteralExpression *) array->GetIndex();
        BOOST_CHECK_EQUAL("person", person->GetName());
        BOOST_CHECK_EQUAL("\"name\"", name->GetValue());
    }

BOOST_AUTO_TEST_SUITE_END()