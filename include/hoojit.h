#ifndef HOOJIT_H
#define HOOJIT_H

#include "hoocodebuffer.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hoo_jit_ins {
        unsigned char bytes[16];
        size_t bytes_count;
    };
    
    struct hoo_jit {
        struct hoo_jit_ins* ins;
        size_t ins_count;
        struct hoo_codebuffer buffer;
    };
    
    typedef void (*hoo_jit_exec)();
    
    struct hoo_jit* hoo_jit_init();
    int hoo_jit_add_instruction(struct hoo_jit* jit, struct hoo_jit_ins ins);
    void hoo_jit_close(struct hoo_jit* jit);
    struct hoo_codebuffer hoo_jit_get_codebuffer(struct hoo_jit* jit);
    hoo_jit_exec hoo_jit_compile(struct hoo_jit* jit);


#ifdef __cplusplus
}
#endif

#endif /* HOOJIT_H */

