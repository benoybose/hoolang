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
 * File: hcexpr.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include "hcexpr.h"
#include <stdlib.h>


struct hc_node_expr_binary* hc_node_expr_binary_create(struct hc_node_expr* lvalue,
            enum hc_type_operator opr, 
            struct hc_node_expr* rvalue) {
    struct hc_node_expr_binary* node = (struct hc_node_expr_binary*)
    malloc(sizeof(struct hc_node_expr_binary));
    node->lvalue = lvalue;
    node->op = opr;
    node->rvalue = rvalue;
    return node;
    
}

struct hc_node_expr* hc_node_expr_create(enum hc_type_expr type, void* value) {
    struct hc_node_expr* node = (struct hc_node_expr*) malloc(sizeof(struct hc_node_expr));
    node->type = type;
    switch(type) {
        case EXPR_TYPE_LITERAL: node->value.literal = (struct hc_node_literal*) value; break;
        case EXPR_TYPE_BINARY: node->value.binary = (struct hc_node_expr_binary*) value; break;
        default: node->value.generic = 0;
    }
    return node;
}
