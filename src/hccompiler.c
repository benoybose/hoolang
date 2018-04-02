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
 * File: hccompiler.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include "hccompiler.h"
#include "hclogger.h"
#include "hclexer.h"
#include "hcparser.h"
#include "nodes/hcprog.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct hc_compiler_context* __hc_compiler_context = 0;
extern int yyparse();

void hc_compiler_context_init() {
    if(0 == __hc_compiler_context) {
        __hc_compiler_context = (struct hc_compiler_context*)
            malloc(sizeof(struct hc_compiler_context));
        __hc_compiler_context->source_files = 0;
        __hc_compiler_context->source_files_count = 0;
        __hc_compiler_context->progs_count = 0;
        __hc_compiler_context->progs = 0;
    }
}

size_t hc_compiler_context_add_source_file(const char* source_file_path) {
	size_t count = __hc_compiler_context->source_files_count + 1;
	if(1 == count) {
		__hc_compiler_context->source_files = 
                        (char**) malloc(sizeof(char*) * count);
	} else {
		__hc_compiler_context->source_files = 
                        (char**) realloc(__hc_compiler_context->source_files, count);
	}

	size_t path_lengh = strlen(source_file_path) + 1;
	__hc_compiler_context->source_files[__hc_compiler_context->source_files_count] = 
                (char*) malloc(sizeof(char) * path_lengh);
	strcpy(__hc_compiler_context->source_files[__hc_compiler_context->source_files_count], 
                source_file_path);
	__hc_compiler_context->source_files_count = count;
	return __hc_compiler_context->source_files_count;
}

size_t hc_compiler_context_add_prog(struct hc_node_prog* prog) {
    
    __hc_compiler_context->progs_count += 1;
    if(1 == __hc_compiler_context->progs_count) {
        __hc_compiler_context->progs = (struct hc_node_prog**)
                malloc(sizeof(struct hc_node_prog*) * __hc_compiler_context->progs_count);
    } else {
        __hc_compiler_context->progs = (struct hc_node_prog**)
                realloc(__hc_compiler_context->progs, __hc_compiler_context->progs_count);
    }
    __hc_compiler_context->progs[__hc_compiler_context->progs_count - 1] = prog;
    return __hc_compiler_context->progs_count;
}

int hc_compiler_context_compile() {
	struct hc_compiler_context* context = __hc_compiler_context;
	for(size_t index = 0; index < context->source_files_count; index++) {
		char* file_path = context->source_files[index];
		FILE* stream = fopen(file_path, "rb");
		if(0 == stream) {
			hclog_print("Failed to open the source file '%s'.\n", file_path);
			return -1;
		}

		yyin = stream;
		do {
			if(0 != yyparse()) {
				printf("Failed to compile '%s'.\n", file_path);
				return -2;
			}
		} while(!feof(yyin));
		fclose(stream);
	}
}

void hc_compiler_context_free() {
    struct hc_compiler_context* context = __hc_compiler_context;
    for(size_t index = 0; index < context->source_files_count; index++) {
        char* file_path = context->source_files[index];
        free(file_path);
    }
    
    free(context->source_files);
    free(context);
}

void yyerror(const char* message) {
    printf("Syntax error: %s.\r\n", message);
}
