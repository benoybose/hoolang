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
 * File: hcbuffer.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 12, April 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "hcbuffer.h"

struct hc_buffer* hc_buffer_create() {
    struct hc_buffer* buffer = (struct hc_buffer*) malloc(sizeof(struct hc_buffer));
    buffer->data = 0;
    buffer->size = 0;
    return buffer;
}

size_t hc_buffer_append(struct hc_buffer* buffer, const char* data, size_t size) {
    size_t total_size = buffer->size + size;
    if(0 == buffer->data) {
        buffer->data = (char*) malloc(sizeof(char) * (total_size + 1));
    } else {
        buffer->data = (char*) realloc(buffer->data, sizeof(char) * (total_size + 1));
    }
    
    memcpy(&buffer->data[buffer->size], data, size);
    buffer->data[total_size] = 0;
    buffer->size = total_size;
    return total_size;
}

size_t hc_buffer_printf(struct hc_buffer* buffer, const char* format, ...) {
    va_list args;
    va_start(args, format);
    size_t length = strlen(format) + 4098;
    char* temp_string = (char*) malloc(sizeof(char) * length);
    vsprintf(temp_string, format, args);
    va_end(args);
    length = strlen(temp_string);
    length = hc_buffer_append(buffer, temp_string, length);
    free(temp_string);
    return length;
}

void hc_buffer_free(struct hc_buffer* buffer) {
    free(buffer->data);
    buffer->data = 0;
    free(buffer);
}

