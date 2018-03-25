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
 * File: hoojitfunccall.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 12, March 2018
 */

#ifndef HOOJITFUNCCALL_H
#define HOOJITFUNCCALL_H

#include <stdint.h>
#include "hootype.h"

#ifdef __cplusplus
extern "C" {
#endif

    /**
     * A JIT function call
     */
    struct hoo_jit_func_call {
        /**
         * Address of the function
         */
        void* func;
        /**
         * Number of parameters
         */
        uint8_t param_count;
        /**
         * Array of parameters
         */
        struct hoo_metaobject** params;
    };
    
    /**
     * Creates a new instance of JIT function call
     * 
     * @param func Address of the function to invoke
     * @return New instance of JIT function call
     */
    
    struct hoo_jit_func_call* hoo_jit_func_call_create(void* func);
    /**
     * Add a new parameter to the function call
     * @param call instance of JIT function call
     * @param param Parameters as hoo metaobject
     * @return Total number of parameters on success, -1 on error
     */
    int hoo_jit_func_call_add_param(struct hoo_jit_func_call* call,
            struct hoo_metaobject* param);

#ifdef __cplusplus
}
#endif

#endif /* HOOJITFUNCCALL_H */

