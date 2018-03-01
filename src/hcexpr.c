#include "hcexpr.h"
#include <stdlib.h>


struct hcexpr_binary_node* hcexpr_binary_node_create(struct hcexpr_node* lvalue,
            enum hcoperator_type opr, 
            struct hcexpr_node* rvalue) {
    struct hcexpr_binary_node* node = (struct hcexpr_binary_node*)
    malloc(sizeof(struct hcexpr_binary_node));
    node->lvalue = lvalue;
    node->op = opr;
    node->rvalue = rvalue;
    return node;
    
}

struct hcexpr_node* hcexpr_node_create(enum hcexpr_type type, void* value) {
    struct hcexpr_node* node = (struct hcexpr_node*) malloc(sizeof(struct hcexpr_node));
    node->type = type;
    switch(type) {
        case EXPR_TYPE_LITERAL: node->value.literal = (struct hclieral_node*) value; break;
        case EXPR_TYPE_BINARY: node->value.binary = (struct hcexpr_binary_node*) value; break;
        default: node->value.generic = 0;
    }
    return node;
}