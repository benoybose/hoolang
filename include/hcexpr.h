/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hcexpr.h
 * Author: benoybose
 *
 * Created on 1 March, 2018, 2:19 AM
 */

#ifndef HCEXPR_H
#define HCEXPR_H

#include "literaltype.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        EXPR_TYPE_LITERAL,
        EXPR_TYPE_BINARY
    } hcexpr_type;
    
    struct hcexpr_node{
        hcexpr_type type;
        union {
            struct hclieral_node* value;
        };
    };

#ifdef __cplusplus
}
#endif

#endif /* HCEXPR_H */

