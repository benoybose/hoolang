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

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hc_compiler_context {
        size_t source_files_count;
        char** source_files;
    };
    
    struct hc_compiler_context* hc_compiler_context_create();
    int hc_compiler_context_add_source_file(struct hc_compiler_context* context, 
            const char* source_file_path);
    int hc_compiler_context_compile(struct hc_compiler_context* context);
    void hc_compiler_context_free(struct hc_compiler_context* context);

#ifdef __cplusplus
}
#endif

#endif /* HCCOMPILER_H */

