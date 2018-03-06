#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "hoojit.h"
#include "stdlib.h"
#include "hoocodebuffer.h"
#include "hooutil.h"

struct hoo_jit* hoo_jit_init() {
    struct hoo_jit* jit = malloc(sizeof(struct hoo_jit));
    jit->ins = 0;
    jit->ins_count = 0;
    jit->buffer.code = 0;
    jit->buffer.code_size = 0;
    return jit;
}

int hoo_jit_add_instruction(struct hoo_jit* jit, 
        struct hoo_jit_ins ins) {
    
    if(0 == jit) {
        return 0;
    }
    
    size_t buffer_size = (jit->ins_count + 1) * sizeof(struct hoo_jit_ins);    
    if(0 == jit->ins) {
        jit->ins = malloc(buffer_size);
    } else {
        jit->ins = realloc(jit->ins, buffer_size);
    }

    jit->ins[jit->ins_count] = ins;
    jit->ins_count ++;
    return jit->ins_count;
}

void hoo_jit_close(struct hoo_jit* jit) {
    if(0 == jit) {
        return;
    }
    
    if(0 != jit->ins) {
        free(jit->ins);
    }
    
    if(0 != jit->buffer.code) {
        hoo_codebuffer_free(jit->buffer);
    }
    
    free(jit);
}

size_t hoo_jit_calculate_buffer_size(struct hoo_jit* jit) {
    if(0 == jit) {
        return 0;
    }
    
    size_t buffer_size = 0;
    for(int index = 0; index < jit->ins_count; index++) {
        struct hoo_jit_ins ins = jit->ins[index];
        buffer_size += ins.bytes_count;
    }
    
    buffer_size += 1; // for appending 0xC3 (RET)
    return buffer_size;
}

struct hoo_codebuffer hoo_jit_get_codebuffer(struct hoo_jit* jit) {
    size_t buffer_size = hoo_jit_calculate_buffer_size(jit);
    struct hoo_codebuffer buffer = hoo_codebuffer_allocate(buffer_size);
    
    size_t pos = 0;
    for(int index = 0; index < jit->ins_count; index++) {
        struct hoo_jit_ins ins = jit->ins[index];
        memcpy(&buffer.code[pos], 
                ins.bytes, 
                ins.bytes_count);
        pos += ins.bytes_count;
    }
    
    buffer.code[buffer_size - 1] = 0xC3; // Appending 0xC3 (RET)
    return buffer;
}

hoo_jit_exec hoo_jit_compile(struct hoo_jit* jit) {
    if(0 != jit->buffer.code) {
        hoo_codebuffer_free(jit->buffer);
    }    
    jit->buffer = hoo_jit_get_codebuffer(jit);
    hoo_codebuffer_lock(jit->buffer);    
    return (hoo_jit_exec) jit->buffer.code;
}

int hoo_jit_add_func_call(struct hoo_jit* jit, struct hoo_jit_func_call func_call) {
    if(4 == sizeof(size_t)) {
        uint32_t address = (uint32_t) func_call.func;
        struct hoo_int32_decoded decoded = hoo_int32_get_decoded(address);
        
        // Creating MOV EAX, ADDRESS
        struct hoo_jit_ins ins_mov_eax_adr = {
            .bytes = { 0xB8, decoded.byte1, decoded.byte2, 
                decoded.byte3, decoded.byte4 },
            .bytes_count = 5
        };
        
        // Creating CALL EAX
        struct hoo_jit_ins ins_call_eax = {
            .bytes = { 0xFF, 0xD0 },
            .bytes_count = 2
        };
        
        hoo_jit_add_instruction(jit, ins_mov_eax_adr);
        hoo_jit_add_instruction(jit, ins_call_eax);
        return jit->ins_count;
        
    } else {
        // todo: Implement for x64
    }
    return 0;
}