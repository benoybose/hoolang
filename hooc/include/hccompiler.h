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
 * File: hccompiler.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#ifndef HCCOMPILER_H
#define HCCOMPILER_H

#include <stdlib.h>

#include "hcbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hc_compiler_context {
        size_t source_files_count;
        char** source_files;
        size_t progs_count;
        struct hc_node_prog** progs;
    };
    
    void hc_compiler_context_init();
    size_t hc_compiler_context_add_source_file(const char* source_file_path);
    size_t hc_compiler_contect_add_prog(struct hc_node_prog* prog);
    int hc_compiler_context_compile();
    size_t hc_compiler_context_serialize(struct hc_buffer* buffer);
    void hc_compiler_context_free();

#ifdef __cplusplus
}
#endif

#endif /* HCCOMPILER_H */

