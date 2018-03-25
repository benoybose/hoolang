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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct hc_compiler_context* __hc_compiler_context = 0;
extern int yyparse();

struct hc_compiler_context* hc_compiler_context_create() {
    struct hc_compiler_context* context = (struct hc_compiler_context*)
    malloc(sizeof(struct hc_compiler_context));
    context->source_files = 0;
    context->source_files_count = 0;
    return context;
}

int hc_compiler_context_add_source_file(struct hc_compiler_context* context,
            const char* source_file_path) {
	size_t count = context->source_files_count + 1;
	if(1 == count) {
		context->source_files = (char**) malloc(sizeof(char*) * count);
	} else {
		context->source_files = (char**) realloc(context->source_files, count);
	}

	size_t path_lengh = strlen(source_file_path) + 1;
	context->source_files[context->source_files_count] = (char*) malloc(sizeof(char) * path_lengh);
	strcpy(context->source_files[context->source_files_count], source_file_path);
	context->source_files_count = count;
	return context->source_files_count;
}

int hc_compiler_context_compile(struct hc_compiler_context* context) {
	__hc_compiler_context = context;
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

void hc_compiler_context_free(struct hc_compiler_context* context) {
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
