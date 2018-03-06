#ifndef HOOCODEBUFFER_H
#define HOOCODEBUFFER_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hoo_codebuffer {
      unsigned char* code;
      size_t code_size;
    };
    
    struct hoo_codebuffer hoo_codebuffer_allocate(size_t size);
    void hoo_codebuffer_lock(struct hoo_codebuffer codebuffer);
    void hoo_codebuffer_free(struct hoo_codebuffer codebuffer);
    void hoo_codebuffer_printf(struct hoo_codebuffer codebuffer);

#ifdef __cplusplus
}
#endif

#endif /* HOOCODEBUFFER_H */

