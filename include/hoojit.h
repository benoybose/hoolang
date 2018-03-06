#ifndef HOOJIT_H
#define HOOJIT_H

#include "hoocodebuffer.h"

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
    
    struct hoo_jit_func_call {
        void* func;
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
    
    int hoo_jit_add_func_call(struct hoo_jit* jit, struct hoo_jit_func_call func_call);


#ifdef __cplusplus
}
#endif

#endif /* HOOJIT_H */

