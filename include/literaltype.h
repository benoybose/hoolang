#ifndef _LITERALTYPE_H_
#define _LITERALTYPE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum {
        LITERAL_TYPE_INT,
        LITERAL_TYPE_LONG,
        LITERAL_TYPE_BYTE,
        LITERAL_TYPE_CHAR,
        LITERAL_TYPE_STRING,
        LITERAL_TYPE_BOOL
    } hcliteral_type;

    struct hclieral_node {
        hcliteral_type type;

        union {
            int32_t intval;
            int64_t longval;
            uint8_t byteval;
            char charval;
            char* stringval;
            bool boolval;
        } value;
        size_t size;
    };

    struct hclieral_node* hcliteral_create(char* text, hcliteral_type literal_type);

#ifdef __cplusplus
}
#endif
#endif
