//
// Created by benoybose on 15/12/18.
//

#include <Listener.hh>

#include "Listener.hh"

namespace hooc
{
    void Listener::enterPrimaryExpression(HooParser::PrimaryExpressionContext *context) {
        HooBaseListener::enterPrimaryExpression(context);
    }

    void Listener::exitPrimaryExpression(HooParser::PrimaryExpressionContext *context) {
        HooBaseListener::exitPrimaryExpression(context);
    }

    void Listener::enterBinaryExpression(HooParser::BinaryExpressionContext *context) {
        HooBaseListener::enterBinaryExpression(context);
    }

    void Listener::exitBinaryExpression(HooParser::BinaryExpressionContext *context) {
        HooBaseListener::exitBinaryExpression(context);
    }

    void Listener::enterExpression(HooParser::ExpressionContext *context) {
        HooBaseListener::enterExpression(context);
    }

    void Listener::exitExpression(HooParser::ExpressionContext *context) {
        HooBaseListener::exitExpression(context);
    }

    void Listener::enterBinaryOperator(HooParser::BinaryOperatorContext *context) {
        HooBaseListener::enterBinaryOperator(context);
    }

    void Listener::exitBinaryOperator(HooParser::BinaryOperatorContext *context) {
        HooBaseListener::exitBinaryOperator(context);
    }
}


