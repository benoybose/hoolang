#define BOOST_TEST_MODULE Arithmetic Statement Test

#include "ArithmeticStmtTest.hh"
#include "ParserDriver.hh"
#include "StatementList.hh"
#include "ExpressionStatement.hh"
#include "LiteralExpression.hh"
#include "TestHelper.hh"

#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace hooc;

BOOST_AUTO_TEST_CASE(Test001_ArithmeticStatementTest) {
    std::stringstream stream("12 + 34;");
    ParserDriver driver(stream, "test");
    BOOST_CHECK(0 == driver.Parse());

    auto statements = driver.GetModule().GetStatements();
    BOOST_CHECK(1 == statements.size());

    auto statement = (*statements.begin()).get();
    BOOST_CHECK(nullptr != statement);
    BOOST_CHECK(hooc::STMT_EXPRESSION == statement->GetStatementType());

    auto expression_statement = (hooc::ExpressionStatement*) statement;
    BOOST_CHECK(nullptr != expression_statement);

    auto expression = expression_statement->GetExpression();
    BOOST_CHECK(nullptr != expression);

    BOOST_CHECK(hooc::EXPRESSION_BINARY ==  expression->GetExpressionType());
    auto binary_expr = (hooc::BinaryExpression*) expression;
    BOOST_CHECK(nullptr != binary_expr);
    auto left = binary_expr->GetLeftExpression();
    auto right = binary_expr->GetRightExpression();
    auto opr = binary_expr->GetOperator();

    BOOST_CHECK(nullptr != left);
    BOOST_CHECK(nullptr != right);
    BOOST_CHECK(nullptr != opr);

    BOOST_CHECK(left->GetExpressionType() == EXPRESSION_LITERAL);
    BOOST_CHECK(right->GetExpressionType() == EXPRESSION_LITERAL);
    BOOST_CHECK(opr->GetNodeType() == NODE_OPERATOR);

    auto left_expr = (LiteralExpression*) left;
    auto right_expr = (LiteralExpression*) right;

    BOOST_CHECK(nullptr != left_expr);
    BOOST_CHECK(nullptr != right_expr);

    BOOST_CHECK(LITERAL_INTEGER == left_expr->GetListeralType());
    BOOST_CHECK(LITERAL_INTEGER == right_expr->GetListeralType());

    BOOST_CHECK(12 == left_expr->GetInteger());
    BOOST_CHECK(34 == right_expr->GetInteger());
}