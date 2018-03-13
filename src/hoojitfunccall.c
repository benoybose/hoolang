#include "hoojitfunccall.h"
#include <stdlib.h>

// Maximum number of paramers is defined as 255 / 4
#define HOO_MAX_PARAMS 63

struct hoo_jit_func_call* hoo_jit_func_call_create(void* func) {
    struct hoo_jit_func_call* call = (struct hoo_jit_func_call*)
    malloc(sizeof(struct hoo_jit_func_call));
    call->func = func;
    call->param_count = 0;
    call->params = 0;
    return call;
}

int hoo_jit_func_call_add_param(struct hoo_jit_func_call* call,
        struct hoo_metaobject* param) {

    if(HOO_MAX_PARAMS <= call->param_count) {
        return -1;
    }
    
    size_t param_size = sizeof(struct hoo_metaobject*) * (call->param_count + 1);
    if(0 == call->param_count) {
        call->params = malloc(param_size);
    } else {
        call->params = realloc(call->params, param_size);
    }
    
    call->params[call->param_count] = param;
    call->param_count ++;
}