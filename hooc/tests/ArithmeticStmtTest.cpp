#include "ArithmeticStmtTest.hh"
#include "ParserDriver.hh"
#include "StatementList.hh"
#include "ExpressionStatement.hh"
#include "LiteralExpression.hh"
#include "TestHelper.hh"

#include <list>
#include <tuple>

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include <sstream>
using namespace CppUnit;
using namespace hooc;

void ArithmeticStmtTest::Test001_12plus34() {
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
    auto binaryExprDetails = TestHelper::VerifyBinaryExpression(expression,
                                       EXPRESSION_LITERAL,
                                       EXPRESSION_LITERAL,
                                       OPERATOR_ADD);
    TestHelper::VerifyLieralExpression(&std::get<0>(binaryExprDetails), LITERAL_INTEGER);
    TestHelper::VerifyLieralExpression(&std::get<2>(binaryExprDetails), LITERAL_INTEGER);
    CPPUNIT_ASSERT(OPERATOR_ADD == std::get<1>(binaryExprDetails).getOperatorType());

    LiteralExpression& left_expression = (LiteralExpression&) std::get<0>(binaryExprDetails);
    LiteralExpression& right_expression = (LiteralExpression&) std::get<2>(binaryExprDetails);
    CPPUNIT_ASSERT(12 == left_expression.GetInteger());
    CPPUNIT_ASSERT(34 == right_expression.GetInteger());

}

CppUnit::Test* ArithmeticStmtTest::suite() {
    TestSuite* arithmeticTestSuite = new TestSuite();
    arithmeticTestSuite->addTest(new TestCaller<ArithmeticStmtTest>("Test001_12plus34",
                                                                    &ArithmeticStmtTest::Test001_12plus34));
    return arithmeticTestSuite;
}
