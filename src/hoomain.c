#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#endif

void test_func() {
    printf("Testing call.\n");
}

unsigned char* hoo_codebuffer_allocate(size_t size) {
    char* buffer = 0;
#ifdef _WIN32
    buffer = VirtualAlloc(NULL, size, 
            MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#endif
    return buffer;
}

void hoo_codebuffer_freeze(char* buffer, size_t size) {
#ifdef _WIN32
    DWORD old = 0;
    VirtualProtect(buffer, size, PAGE_EXECUTE_READ, &old);
#endif
}

int main() {
    unsigned int func_addresses[] = { (unsigned int) test_func };
    printf("Function: %p Indirect: %p Address: %p",
            &test_func, 
            func_addresses[0], (void*) func_addresses);
    char code[] = { 0xB8, 0x60, 0x14, 0x40, 0x00, 0xFF, 0xD0, 0xC3 };
    printf("Going to allocate.\n");
    char* buffer = hoo_codebuffer_allocate(8);
    memcpy(buffer, code, 8);
    hoo_codebuffer_freeze(buffer, 8);

    printf("Going to call.\n");
    void (*foo)() = (void*) buffer;
    foo();
    printf("Called.\n");    
    return 0;    
}