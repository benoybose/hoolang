/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hccompiler.h
 * Author: COMP
 *
 * Created on 23 March, 2018, 8:35 PM
 */

#ifndef HCCOMPILER_H
#define HCCOMPILER_H

#ifdef __cplusplus
extern "C" {
#endif
    
    struct hc_compiler_context {
        size_t source_files_count;
        char** source_files;
    };
    
    struct hc_compiler_context* hc_compiler_context_create();
    int hc_compiler_context_add_source_file(struct hc_compiler_context* context, 
            const char* source_file_path);
    int hc_compiler_context_compile(struct hc_compiler_context* context);
    void hc_compiler_context_free(struct hc_compiler_context* context);


#ifdef __cplusplus
}
#endif

#endif /* HCCOMPILER_H */

