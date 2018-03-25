/*
 * Copyright 2018 Benoy Bose
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/**
 * File: hoojit.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "hootype.h"
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
    
    struct hoo_jit_ins ins_push_ebp = {
        .bytes = { 0x55 },
        .bytes_count = 1
    };
    
    struct hoo_jit_ins ins_mov_esp_ebp = {
        .bytes = { 0x89, 0xE5 },
        .bytes_count = 2
    };
    
    hoo_jit_add_instruction(jit, ins_push_ebp);
    hoo_jit_add_instruction(jit, ins_mov_esp_ebp);
    
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
    
    return buffer_size;
}

struct hoo_codebuffer hoo_jit_get_codebuffer(struct hoo_jit* jit) {
    size_t buffer_size = hoo_jit_calculate_buffer_size(jit);
    buffer_size += 2;
    
    struct hoo_codebuffer buffer = hoo_codebuffer_allocate(buffer_size);    
    size_t pos = 0;
    for(int index = 0; index < jit->ins_count; index++) {
        struct hoo_jit_ins ins = jit->ins[index];
        memcpy(&buffer.code[pos], 
                ins.bytes, 
                ins.bytes_count);
        pos += ins.bytes_count;
    }
    
    buffer.code[buffer_size - 2] = 0xC9; // Appending 0xC9 LEAVE
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

int hoo_jit_add_func_call(struct hoo_jit* jit, struct hoo_jit_func_call* call) {
    if(4 == sizeof(size_t)) {
        uint32_t address = (uint32_t) call->func;
        
        // Decoding function address to four bytes
        struct hoo_uint32_decoded decoded = hoo_uint32_get_decoded(address);        
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
        
        if(0 < call->param_count) {
            
            // Calculating total size in stack for function parameters
            uint8_t stack_offset = call->param_count * 4;
            
            // JIT instruction to expand stack for function parameters by
            // substracting the ESP
            struct hoo_jit_ins ins_sub_esp = {
                .bytes = { 0x83, 0xEC, stack_offset },
                .bytes_count = 3
            };            
            if(0x80 == (0x80 & stack_offset)) {
                ins_sub_esp.bytes[0] = 0x81;
            }            
            hoo_jit_add_instruction(jit, ins_sub_esp);
            
            for(int index = 0; index < call->param_count; index++) {
                uint8_t reverse_index = call->param_count - (index + 1);
                uint8_t param_pos = reverse_index * 4;
                struct hoo_metaobject* object = call->params[reverse_index];
                struct hoo_uint32_decoded param_address = hoo_uint32_get_decoded((uint32_t) object);
                if(0 < param_pos) {
                    struct hoo_jit_ins ins_mov_esp = {
                        .bytes = { 0xC7, 0x44, 0x24, param_pos,
                        param_address.byte1,
                        param_address.byte2,
                        param_address.byte3,
                        param_address.byte4},
                        .bytes_count = 8
                    };
                    hoo_jit_add_instruction(jit, ins_mov_esp);
                } else {
                    struct hoo_jit_ins ins_mov_esp = {
                        .bytes = { 0xC7, 0x04, 0x24, 
                        param_address.byte1,
                        param_address.byte2,
                        param_address.byte3,
                        param_address.byte4},
                        .bytes_count = 7
                    };
                    hoo_jit_add_instruction(jit, ins_mov_esp);
                }                
            }
        }
        
        hoo_jit_add_instruction(jit, ins_mov_eax_adr);
        hoo_jit_add_instruction(jit, ins_call_eax);
        
        if(call) {
            if(call->param_count) {
                free(call->params);
            }
            free(call);
        }
        
        return jit->ins_count;
        
    } else {
        // todo: Implement for x64
    }
    return 0;
}
