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
 * File: hoomain.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hoojit.h"

void test_func() {
    printf("Hello, JIT!\n");
}

int test_int(struct hoo_metaobject* p1, struct hoo_metaobject* p2) {
    printf("%d + %d = %d\n", p1->value._int32, p2->value._int32, 
            (p1->value._int32 + p2->value._int32));
    return 0;
}

int main() {   
    struct hoo_jit* jit = hoo_jit_init();
    struct hoo_jit_func_call* func_call = hoo_jit_func_call_create(&test_func);
    hoo_jit_add_func_call(jit, func_call);
    
    struct hoo_jit_func_call* call = hoo_jit_func_call_create(&test_int);
    struct hoo_metaobject* p1 = hoo_metaobject_create_int32(3);
    struct hoo_metaobject* p2 = hoo_metaobject_create_int32(4);
    hoo_jit_func_call_add_param(call, p1);
    hoo_jit_func_call_add_param(call, p2);
    hoo_jit_add_func_call(jit, call);
    hoo_jit_exec test = hoo_jit_compile(jit);
    test();
    return 0;
}
