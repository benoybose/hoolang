//
// Created by COMP on 24-06-2018.
//

#ifndef HOOC_TESTHELPER_HH
#define HOOC_TESTHELPER_HH

#include "Expression.hh"
#include "LiteralExpression.hh"
#include "Operator.hh"

#include <tuple>

using namespace hooc;

class TestHelper {
public:
    static std::tuple<Expression&, Operator&, Expression&> VerifyBinaryExpression(
            Expression* input_expression,
            ExpressionType left_expression_type,
            ExpressionType right_expression_type,
            OperatorType operator_type);

    static void VerifyLieralExpression(Expression* input_expression,
                                       hooc::LiteralType literalType);
};


#endif //HOOC_TESTHELPER_HH
