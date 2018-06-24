//
// Created by COMP on 24-06-2018.
//

#ifndef HOOC_TESTHELPER_HH
#define HOOC_TESTHELPER_HH

#include "Expression.hh"
#include "Operator.hh"

using namespace hooc;

class TestHelper {
public:
    static void VerifyBinaryExpression(
            Expression* input_expression,
            ExpressionType left_expression_type,
            ExpressionType right_expression_type,
            OperatorType operator_type,
            Expression* left_expression,
            Expression* right_expression);
};


#endif //HOOC_TESTHELPER_HH
