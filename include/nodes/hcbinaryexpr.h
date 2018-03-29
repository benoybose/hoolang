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
 * File: hcbinaryexpr.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 28, March 2018
 */

#ifndef HCBINARYEXP_H
#define HCBINARYEXP_H

#include "hcnode.h"
#include "hcoperator.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hc_node_binary_expr {
        enum HC_TYPE_NODE node_type;
        struct hc_node* lvalue;
        struct hc_node_operator* opr;
        struct hc_node* rvalue;
    };
    
    struct hc_node_binary_expr* hc_node_binary_expr_create(
            struct hc_node* lvalue,
            struct hc_node_operator* opr,
            struct hc_node* rvalue);

#ifdef __cplusplus
}
#endif

#endif /* HCBINARYEXPR_H */

