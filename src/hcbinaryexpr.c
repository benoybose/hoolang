/*
 * Copyright 2018 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * File: hcbinaryexpr.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 28, March 2018
 */

#include <stdlib.h>

#include "nodes/hcbinaryexpr.h"

struct hc_node_binary_expr* hc_node_binary_expr_create(
            struct hc_node_expr* lvalue,
            struct hc_node_operator* opr,
            struct hc_node_expr* rvalue) {
    struct hc_node_binary_expr* binary_expr = (struct hc_node_binary_expr*)
        malloc(sizeof(struct hc_node_binary_expr));
    
    binary_expr->node_type = HC_NODE_BINARY_EXPRESSION;
    binary_expr->expr_type = HC_EXPR_BINARY;
    
    binary_expr->lvalue = lvalue;
    binary_expr->opr = opr;
    binary_expr->rvalue = rvalue;
    return binary_expr;
}