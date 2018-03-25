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
 * File: hoonumop.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 9, March 2018
 */

#ifndef HOONUMOP_H
#define HOONUMOP_H

#include "hootype.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    enum  HOO_NUM_OPERATORS{
        HOO_NUM_OP_ADD,
        HOO_NUM_OP_SUB,
        HOO_NUM_OP_DIV,
        HOO_NUM_OP_MUL,
        HOO_NUM_OP_MOD
    };
    
    struct hoo_metaobject* __hoo_num_calc(struct hoo_metaobject* op1, struct hoo_metaobject* op2,
            enum HOO_NUM_OPERATORS op);
    struct hoo_metaobject* __hoo_num_add(struct hoo_metaobject* op1, struct hoo_metaobject* op2);
    struct hoo_metaobject* __hoo_num_sub(struct hoo_metaobject* op1, struct hoo_metaobject* op2);
    struct hoo_metaobject* __hoo_num_div(struct hoo_metaobject* op1, struct hoo_metaobject* op2);
    struct hoo_metaobject* __hoo_num_mul(struct hoo_metaobject* op1, struct hoo_metaobject* op2);
    struct hoo_metaobject* __hoo_num_mod(struct hoo_metaobject* op1, struct hoo_metaobject* op2);
    
    
#ifdef __cplusplus
}
#endif

#endif /* HOONUMOP_H */

