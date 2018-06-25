//
// Created by COMP on 24-06-2018.
//

#include "TestHelper.hh"
#include "BinaryExpression.hh"
#include "LiteralExpression.hh"
#include "Operator.hh"

#include <tuple>

#include <cppunit/TestAssert.h>

using namespace CppUnit;
using namespace hooc;

std::tuple<Expression&, Operator&, Expression&> TestHelper::VerifyBinaryExpression(Expression *input_expression,
                                        ExpressionType left_expression_type,
                                        ExpressionType right_expression_type,
                                        OperatorType operator_type) {
    CPPUNIT_ASSERT_MESSAGE("Expression must be a binary expression.",
                           hooc::EXPRESSION_BINARY == input_expression->GetExpressionType());
    BinaryExpression* binary_expression = (BinaryExpression*) input_expression;
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
    CPPUNIT_ASSERT(left_expression_type == left_expression->GetExpressionType());
    CPPUNIT_ASSERT(right_expression_type == right_expression->GetExpressionType());
    CPPUNIT_ASSERT(operator_type == the_operator->getOperatorType());
    return std::tuple<Expression&, Operator&, Expression&>(
            *left_expression,
            *the_operator,
            *right_expression);
}

void TestHelper::VerifyLieralExpression(Expression *input_expression, hooc::LiteralType literalType) {
    CPPUNIT_ASSERT(EXPRESSION_LITERAL == input_expression->GetExpressionType());
    LiteralExpression* literal_expression = (LiteralExpression*) input_expression;
    CPPUNIT_ASSERT(literalType == literal_expression->GetListeralType());
}
