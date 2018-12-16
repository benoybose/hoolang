#ifndef LISTENER_HH
#define LISTENER_HH

#include "HooBaseListener.h"

namespace hooc
{
    class Listener: public HooBaseListener {
    public:
        void enterPrimaryExpression(HooParser::PrimaryExpressionContext *context) override;

        void exitPrimaryExpression(HooParser::PrimaryExpressionContext *context) override;

        void enterBinaryExpression(HooParser::BinaryExpressionContext *context) override;

        void exitBinaryExpression(HooParser::BinaryExpressionContext *context) override;

        void enterExpression(HooParser::ExpressionContext *context) override;

        void exitExpression(HooParser::ExpressionContext *context) override;

        void enterBinaryOperator(HooParser::BinaryOperatorContext *context) override;

        void exitBinaryOperator(HooParser::BinaryOperatorContext *context) override;

    };
}

#endif //PROJECT_LISTENER_HH
