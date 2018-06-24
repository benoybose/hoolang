#include "ArithmeticStmtTest.hh"
#include "ParserDriver.hh"
#include "StatementList.hh"
#include "ExpressionStatement.hh"
#include "TestHelper.hh"

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
    Expression leftExpression(EXPRESSION_INVALID);
    Expression rightExpression(EXPRESSION_INVALID);
    TestHelper::VerifyBinaryExpression(expression, EXPRESSION_LITERAL,
                                       EXPRESSION_LITERAL, OPERATOR_ADD,
                                       &leftExpression, &rightExpression);

}

CppUnit::Test* ArithmeticStmtTest::suite() {
    TestSuite* arithmeticTestSuite = new TestSuite();
    arithmeticTestSuite->addTest(new TestCaller<ArithmeticStmtTest>("SimpleTest",
                                                                      &ArithmeticStmtTest::SimpleTest));
    return arithmeticTestSuite;
}
