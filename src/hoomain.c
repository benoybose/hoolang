#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hoojit.h"

void test_func() {
    printf("Testing call.\n");
}

//unsigned char* hoo_codebuffer_allocate(size_t size) {
//    char* buffer = 0;
//#ifdef _WIN32
//    buffer = VirtualAlloc(NULL, size, 
//            MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
//#endif
//    return buffer;
//}
//
//void hoo_codebuffer_freeze(char* buffer, size_t size) {
//#ifdef _WIN32
//    DWORD old = 0;
//    VirtualProtect(buffer, size, PAGE_EXECUTE_READ, &old);
//#endif
//}

int main() {   
    struct hoo_jit* jit = hoo_jit_init();
    struct hoo_jit_ins ins_mov_address_to_eax = {
        .bytes = {0xB8, 0x60, 0x14, 0x40, 0x00}, 
        .bytes_count = 5
    };
    struct hoo_jit_ins ins_call_eax = {
        .bytes = { 0xFF, 0xD0 }, 
        .bytes_count = 2
    };
    struct hoo_jit_ins ins_ret = {
        .bytes = { 0xC3 }, 
        .bytes_count = 1
    };
    
    hoo_jit_add_instruction(jit, ins_mov_address_to_eax);
    hoo_jit_add_instruction(jit, ins_call_eax);
    hoo_jit_add_instruction(jit, ins_ret);
    hoo_jit_exec jit_exec = hoo_jit_compile(jit);
    jit_exec();
    
    unsigned int func_addresses[] = { (unsigned int) test_func };
    printf("Function: %p Indirect: %p Address: %p",
            &test_func, 
            func_addresses[0], (void*) func_addresses);
//    char code[] = { 0xB8, 0x60, 0x14, 0x40, 0x00, 0xFF, 0xD0, 0xC3 };
//    printf("Going to allocate.\n");
//    char* buffer = hoo_codebuffer_allocate(8);
//    memcpy(buffer, code, 8);
//    hoo_codebuffer_freeze(buffer, 8);
//
//    printf("Going to call.\n");
//    void (*foo)() = (void*) buffer;
//    foo();
//    printf("Called.\n");    
    return 0;    
}