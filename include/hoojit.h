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
 * File: hoojit.h
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#ifndef HOOJIT_H
#define HOOJIT_H

#include "hoocodebuffer.h"
#include "hootype.h"
#include "hoojitfunccall.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    /**
     * A JIT instruction
     */
    struct hoo_jit_ins {
        /**
         * Instruction bytes
         */
        unsigned char bytes[16];
        /**
         * Number of bytes in the instruction
         */
        size_t bytes_count;
    };
    
    /**
     * A JIT compiler context
     */
    struct hoo_jit {
        /**
         * Pointer to a list of instructions
         */
        struct hoo_jit_ins* ins;
        /**
         * Total number of instructions
         */
        size_t ins_count;
        /**
         * Compiled output as code buffer
         */
        struct hoo_codebuffer buffer;
    };
    
    /**
     * Function pointer type JIT executable.
     * 
     * Invoking instance of this function may execute a JIT compiled code
     */
    typedef void (*hoo_jit_exec)();
    
    /**
     * Initialize a JIT compiler context
     * @return JIT compiler context
     */
    struct hoo_jit* hoo_jit_init();
    
    /**
     * Adds a JIT instruction to the context
     * 
     * @param jit JIT compiler context
     * @param ins Instance of JIT instruction
     * @return Total number of instructions in the context
     */
    int hoo_jit_add_instruction(struct hoo_jit* jit, 
            struct hoo_jit_ins ins);
    
    /**
     * Release a JIT compiler context
     * @param jit JIT compiler context
     */
    void hoo_jit_close(struct hoo_jit* jit);
    
    /**
     * Create code buffer from instructions in the context
     * @param jit JIT compiler context
     * @return Code buffer
     */
    struct hoo_codebuffer hoo_jit_get_codebuffer(struct hoo_jit* jit);
    
    /**
     * Compile the JIT context to an executable function
     * 
     * @param jit JIT compiler context
     * @return A pointer to a function to execute the compiled code
     */
    hoo_jit_exec hoo_jit_compile(struct hoo_jit* jit);
    
    int hoo_jit_add_func_call(struct hoo_jit* jit, struct hoo_jit_func_call* func_call);


#ifdef __cplusplus
}
#endif

#endif /* HOOJIT_H */

