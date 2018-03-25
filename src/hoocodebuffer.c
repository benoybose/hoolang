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
 * File: hoocodebuffer.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/mman.h>
#endif

#include "hoocodebuffer.h"

struct hoo_codebuffer hoo_codebuffer_allocate (size_t size) {
    char *buffer = 0;
#ifdef _WIN32
    buffer = VirtualAlloc(NULL, size, 
            MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
    buffer = mmap(0, size, 
        PROT_READ | PROT_WRITE, 
        MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
#endif
    struct hoo_codebuffer codebuffer;
    codebuffer.code = buffer;
    codebuffer.code_size = size;
    return codebuffer;
}

void hoo_codebuffer_lock(struct hoo_codebuffer codebuffer) {
#ifdef _WIN32
    DWORD old = 0;
    VirtualProtect(codebuffer.code, codebuffer.code_size, 
            PAGE_EXECUTE_READ, &old);
#else
    mprotect(codebuffer.code, codebuffer.code_size, 
        PROT_READ | PROT_EXEC);
#endif
}

void hoo_codebuffer_free(struct hoo_codebuffer codebuffer) {
#ifdef _WIN32
    VirtualFree(codebuffer.code, codebuffer.code_size, MEM_RELEASE);
#else
    munmap(codebuffer.code, codebuffer.code_size);
#endif
}

void hoo_codebuffer_printf(struct hoo_codebuffer codebuffer) {
    printf("[");
    for(int index = 0; index < codebuffer.code_size; index++) {
        printf("%02x", codebuffer.code[index]);
        if(index < (codebuffer.code_size - 1)) {
            printf(" ");
        }
    }
    printf("]");
}

