#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include "literaltype.h"

struct hclieral_node* hcliteral_node_create(char* text, hcliteral_type literal_type) {
    struct hclieral_node* node = (struct hclieral_node*) malloc(sizeof (struct hclieral_node));
    switch (literal_type) {
        case LITERAL_TYPE_INT:
            node->value.intval = atol(text);
            node->size = sizeof (int32_t);
            break;
            
        case LITERAL_TYPE_LONG: 
            node->value.longval = atoll(text);
            node->size = sizeof (int64_t);
            break;
            
        case LITERAL_TYPE_CHAR: 
            node->value.charval = text[0];
            node->size = sizeof (int8_t);
            break;
            
        case LITERAL_TYPE_BYTE:
            node->value.byteval = (uint8_t) text[0];
            node->size = sizeof(uint8_t);
            break;
            
        case LITERAL_TYPE_STRING:
            node->value.stringval = text;
            node->size = strlen(text);
            break;
    }
    return node;
}
