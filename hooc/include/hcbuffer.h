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
 * File: hcbuffer.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 12, April 2018
 */

#ifndef HCBUFFER_H
#define HCBUFFER_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hc_buffer {
        char* data;
        size_t size;
    };
    
    struct hc_buffer* hc_buffer_create();
    size_t hc_buffer_append(struct hc_buffer* buffer, const char* data, size_t size);
    size_t hc_buffer_printf(struct hc_buffer* buffer, const char* format, ...);
    void hc_buffer_free(struct hc_buffer* buffer);

#ifdef __cplusplus
}
#endif

#endif /* HCBUFFER_H */

