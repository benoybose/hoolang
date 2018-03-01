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

    enum hcexpr_type {
        EXPR_TYPE_LITERAL,
        EXPR_TYPE_BINARY
    };

    enum hcoperator_type {
        OPERATOR_ADD,
        OPERATOR_SUB,
        OPERATOR_DIV,
        OPERATOR_MUL,
        OPERATOR_MOD
    };

    struct hcexpr_node;
    struct hcexpr_binary_node {
        struct hcexpr_node* lvalue;
        enum hcoperator_type op;
        struct hcexpr_node* rvalue;
    };

    struct hcexpr_node {
        enum hcexpr_type type;

        union {
            struct hclieral_node* literal;
            struct hcexpr_binary_node* binary;
            void* generic;
        } value;
    };
    
    struct hcexpr_binary_node* hcexpr_binary_node_create(struct hcexpr_node* lvalue,
            enum hcoperator_type opr, 
            struct hcexpr_node* rvalue);
    struct hcexpr_node* hcexpr_node_create(enum hcexpr_type type, void* value);
    

#ifdef __cplusplus
}
#endif

#endif /* HCEXPR_H */

