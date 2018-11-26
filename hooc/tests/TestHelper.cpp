//
// Created by COMP on 24-06-2018.
//

#define BOOST_TEST_NO_MAIN

#include "TestHelper.hh"
#include "BinaryExpression.hh"
#include "LiteralExpression.hh"
#include "Operator.hh"

#include <tuple>
#include <boost/test/included/unit_test.hpp>

using namespace hooc;

std::tuple<Expression&, Operator&, Expression&> TestHelper::VerifyBinaryExpression(Expression *input_expression,
                                        ExpressionType left_expression_type,
                                        ExpressionType right_expression_type,
                                        OperatorType operator_type) {
    BOOST_CHECK(hooc::EXPRESSION_BINARY == input_expression->GetExpressionType());
    BinaryExpression* binary_expression = (BinaryExpression*) input_expression;
    BOOST_CHECK(nullptr != binary_expression);
    Expression* left_expression = binary_expression->GetLeftExpression();
    Expression* right_expression = binary_expression->GetRightExpression();
    Operator* the_operator = binary_expression->GetOperator();
    BOOST_CHECK(nullptr != left_expression);
    BOOST_CHECK(nullptr != right_expression);
    BOOST_CHECK(nullptr != the_operator);
    BOOST_CHECK(left_expression_type == left_expression->GetExpressionType());
    BOOST_CHECK(right_expression_type == right_expression->GetExpressionType());
    BOOST_CHECK(operator_type == the_operator->getOperatorType());
    return std::tuple<Expression&, Operator&, Expression&>(
            *left_expression,
            *the_operator,
            *right_expression);
}

void TestHelper::VerifyLieralExpression(Expression *input_expression, hooc::LiteralType literalType) {
    BOOST_CHECK(EXPRESSION_LITERAL == input_expression->GetExpressionType());
    LiteralExpression* literal_expression = (LiteralExpression*) input_expression;
    BOOST_CHECK(literalType == literal_expression->GetListeralType());
}
