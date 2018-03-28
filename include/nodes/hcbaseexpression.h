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
 * File: hcbaseexpression.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#ifndef HCBASEEXPRESSION_H
#define HCBASEEXPRESSION_H

#include "hcnode.h"

#ifdef __cplusplus
extern "C" {
#endif

    enum HC_TYPE_BASE_EXPRESSION {
        HC_BASE_EXPRESSION_LITERAL,
        HC_BASE_EXPRESSION_VAR_REFERENCE
    };
    
    struct hc_node_base_expression {
        enum HC_TYPE_NODE node_type;
        enum HC_TYPE_BASE_EXPRESSION base_expression_type;
        struct hc_node* node;
    };
    
    struct hc_node_base_expression* hc_base_expression_create(
            enum HC_TYPE_BASE_EXPRESSION base_expression_type,
            struct hc_node* node);

#ifdef __cplusplus
}
#endif

#endif /* HCBASEEXPRESSION_H */

