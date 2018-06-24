#include "ArithmeticStmtTest.hh"
#include "ParserDriver.hh"
#include "StatementList.hh"
#include "ExpressionStatement.hh"

#include <list>

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <sstream>
using namespace CppUnit;
using namespace hooc;

void ArithmeticStmtTest::SimpleTest() {
    std::stringstream stream("12 + 34;");
    ParserDriver driver(stream, "test");
    CPPUNIT_ASSERT_MESSAGE("Parser should parse a single arithmetic statement.",
                           0 == driver.Parse());
    const std::list<hooc::ast::Statement>& statements = driver
            .GetModule().GetStatements();
    CPPUNIT_ASSERT_MESSAGE("There should be only one statement.",
                           1 == statements.size());
    Statement* statement = (*statements.begin()).get();
    CPPUNIT_ASSERT_MESSAGE("Statement should not be null.",
                           nullptr != statement);
    CPPUNIT_ASSERT_MESSAGE("Statement type should be expression.",
                           hooc::STMT_EXPRESSION == statement->GetStatementType());
    hooc::ExpressionStatement* expression_statement = (hooc::ExpressionStatement*) statement;
    CPPUNIT_ASSERT_MESSAGE("Expression statement must not be null.",
                           nullptr != expression_statement);
    hooc::Expression* expression = expression_statement->GetExpression();
    CPPUNIT_ASSERT_MESSAGE("Expression must not be null.",
                           nullptr != expression);
    CPPUNIT_ASSERT_MESSAGE("Expression must be a binary expression.",
                           hooc::EXPRESSION_BINARY == expression->GetExpressionType());
    BinaryExpression* binary_expression = (BinaryExpression*) expression;
    CPPUNIT_ASSERT_MESSAGE("Binary expression must not be null.",
                           nullptr != binary_expression);
    Expression* left_expression = binary_expression->GetLeftExpression();
    Expression* right_expression = binary_expression->GetRightExpression();
    Operator* the_operator = binary_expression->GetOperator();
    CPPUNIT_ASSERT_MESSAGE("Left expression must not be null.",
                           nullptr != left_expression);
    CPPUNIT_ASSERT_MESSAGE("Right expression must not be null.",
                           nullptr != right_expression);
    CPPUNIT_ASSERT_MESSAGE("Operator must not be null.",
                           nullptr != the_operator);
    CPPUNIT_ASSERT_MESSAGE("Left expression must be literal expression.",
                           EXPRESSION_LITERAL == left_expression->GetExpressionType());
    CPPUNIT_ASSERT_MESSAGE("Right expression must be literal expression.",
                           EXPRESSION_LITERAL == right_expression->GetExpressionType());
    CPPUNIT_ASSERT_MESSAGE("The operator must be add operator.", OPERATOR_ADD == the_operator->getOperatorType());
}

CppUnit::Test* ArithmeticStmtTest::suite() {
    TestSuite* arithmeticTestSuite = new TestSuite();
    arithmeticTestSuite->addTest(new TestCaller<ArithmeticStmtTest>("SimpleTest",
                                                                      &ArithmeticStmtTest::SimpleTest));
    return arithmeticTestSuite;
}
