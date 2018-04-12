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
#include <string.h>
#include "hclogger.h"
#include "hccompiler.h"

int main(int argc, char** argv) {
    hclog_init(stdout);

    if (1 >= argc) {
        printf("No source files specified.\n");
        return 1;
    } else {
        hc_compiler_context_init();
        for (int index = 1; index < argc; index++) {
            const char* parameter = argv[index];
            if('-' == parameter[0]) {                
                if(1 == strlen(parameter)) {
                    printf("Invalid command line argument.\n");
                    return 2;
                }                
                switch(parameter[1]) {
                    case 'i':
                        break;
                    default:
                        printf("Invalid option.\n");
                        return 3;
                }                
            } else {
                char* file_path = argv[index];
                hc_compiler_context_add_source_file(file_path);
            }
        }

        if(0 == hc_compiler_context_compile()) {
            hclog_print("compilation is successfull.");
        }
        hc_compiler_context_free();
        
    }

    hclog_close();
    return 0;
}
