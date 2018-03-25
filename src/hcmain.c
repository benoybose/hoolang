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
 * File: hcmain.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include <stdio.h>
#include "hclogger.h"
#include "hccompiler.h"

int main(int argc, char** argv) {
    hclog_init(stdout);

    if(1 >= argc) {
    	printf("No source files specified.\n");
    	return 1;
    } else {
    	struct hc_compiler_context* context = hc_compiler_context_create();
    	for(int index = 1; index < argc; index++) {
    		char* file_path = argv[index];
    		hc_compiler_context_add_source_file(context, file_path);
    	}

    	hc_compiler_context_compile(context);
    	hc_compiler_context_free(context);
    }

    hclog_close();
    return 0;
}
