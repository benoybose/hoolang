#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hoojit.h"

void test_func() {
    printf("Hello, JIT!\n");
}

int test_int(struct hoo_metaobject* p1, struct hoo_metaobject* p2) {
    printf("%d + %d = %d\n", p1->value._int32, p2->value._int32, 
            (p1->value._int32 + p2->value._int32));
    return 0;
}

int main() {   
    struct hoo_jit* jit = hoo_jit_init();
    struct hoo_jit_func_call* func_call = hoo_jit_func_call_create(&test_func);
    hoo_jit_add_func_call(jit, func_call);
    
    struct hoo_jit_func_call* call = hoo_jit_func_call_create(&test_int);
    struct hoo_metaobject* p1 = hoo_metaobject_create_int32(3);
    struct hoo_metaobject* p2 = hoo_metaobject_create_int32(4);
    hoo_jit_func_call_add_param(call, p1);
    hoo_jit_func_call_add_param(call, p2);
    hoo_jit_add_func_call(jit, call);
    hoo_jit_exec test = hoo_jit_compile(jit);
    test();
    return 0;
}
