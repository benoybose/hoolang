/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hoonumop.h
 * Author: COMP
 *
 * Created on 9 March, 2018, 8:12 PM
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
    
    struct hoo_metaobject* __hoo_num_cal(struct hoo_metaobject* op1, struct hoo_metaobject* op2,
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

