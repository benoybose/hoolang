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
 * File: hoojitfunccall.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include "hoojitfunccall.h"
#include <stdlib.h>

// Maximum number of parameters is defined as 255 / 4
#define HOO_MAX_PARAMS 63

struct hoo_jit_func_call* hoo_jit_func_call_create(void* func) {
    struct hoo_jit_func_call* call = (struct hoo_jit_func_call*)
    malloc(sizeof(struct hoo_jit_func_call));
    call->func = func;
    call->param_count = 0;
    call->params = 0;
    return call;
}

int hoo_jit_func_call_add_param(struct hoo_jit_func_call* call,
        struct hoo_metaobject* param) {

    if(HOO_MAX_PARAMS <= call->param_count) {
        return -1;
    }
    
    size_t param_size = sizeof(struct hoo_metaobject*) * (call->param_count + 1);
    if(0 == call->param_count) {
        call->params = malloc(param_size);
    } else {
        call->params = realloc(call->params, param_size);
    }
    
    call->params[call->param_count] = param;
    call->param_count ++;
    return call->param_count;
}
