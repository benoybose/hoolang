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
 * File: hcliteral.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

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
    } hc_type_literal;

    struct hc_node_literal {
        hc_type_literal type;
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

    struct hc_node_literal* hc_node_literal_create(char* text, hc_type_literal literal_type);

#ifdef __cplusplus
}
#endif
#endif
