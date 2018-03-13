#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hoojit.h"

void test_func() {
    printf("Hello, JIT!");
}

int main() {   
    struct hoo_jit* jit = hoo_jit_init();
    struct hoo_jit_func_call* func_call = hoo_jit_func_call_create(&test_func);
    hoo_jit_add_func_call(jit, func_call);
    hoo_jit_exec test = hoo_jit_compile(jit);
    test();
    return 0;    
}