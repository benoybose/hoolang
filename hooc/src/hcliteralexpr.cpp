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
 * File: literaltype.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <stdlib.h>
#include <stdint.h>
#include <memory.h>

#include "hcliteralexpr.hh"
#include "hcnode.hh"
#include "hcexpr.hh"

struct hc_node_literal_expr* hc_node_literal_expr_create(char* text, enum HC_TYPE_LITERAL literal_type) {
    struct hc_node_literal_expr* node = (struct hc_node_literal_expr*) malloc(sizeof (struct hc_node_literal_expr));

    node->node_type = HC_NODE_LITERAL;
    node->expr_type = HC_EXPR_LITERAL;
    
    switch (literal_type) {
        case HC_LITERAL_INT32:
            node->value.intval = atol(text);
            node->size = sizeof (int32_t);
            break;
            
        case HC_LITERAL_INT64: 
            node->value.longval = atoll(text);
            node->size = sizeof (int64_t);
            break;
            
        case HC_LITERAL_CHAR: 
            node->value.charval = text[0];
            node->size = sizeof (int8_t);
            break;
            
        case HC_LITERAL_BYTE:
            node->value.byteval = (uint8_t) text[0];
            node->size = sizeof(uint8_t);
            break;
            
        case HC_LITERAL_STRING:
            node->value.stringval = text;
            node->size = strlen(text);
            break;
    }
    return node;
}
