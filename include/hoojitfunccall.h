/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hoojitfunccall.h
 * Author: COMP
 *
 * Created on 12 March, 2018, 10:20 PM
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

