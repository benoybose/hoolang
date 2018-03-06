#include <stdio.h>
#ifdef _WIN32
#include "windows.h"
#endif

#include "hoocodebuffer.h"

struct hoo_codebuffer hoo_codebuffer_allocate (size_t size) {
    char *buffer = 0;
#ifdef _WIN32
    buffer = VirtualAlloc(NULL, size, 
            MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
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
#endif
}

void hoo_codebuffer_free(struct hoo_codebuffer codebuffer) {
#ifdef _WIN32
    VirtualFree(codebuffer.code, codebuffer.code_size, MEM_RELEASE);
#endif
}

void hoo_codebuffer_printf(struct hoo_codebuffer codebuffer) {
    printf("[");
    for(int index = 0; index < codebuffer.code_size; index++) {
        printf("%x", codebuffer.code[index]);
        if(index < (codebuffer.code_size - 1)) {
            printf(" ");
        }
    }
    printf("]");
}

