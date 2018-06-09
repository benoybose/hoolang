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
 * File: hclogger.c
 * Author: Benoy Bose <benoybose@gmail.com>
 * Date: 25, March 2018
 */

#include "hclogger.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

FILE* __hc_logfile = 0;

int hclog_print(const char* format, ...) {
    if (0 != __hc_logfile) {
        va_list args;
        va_start(args, format);
        int returnCode = vfprintf(__hc_logfile, format, args);
        if(0 < returnCode) {
            fprintf(__hc_logfile, "%s", "\n");
        }
        va_end(args);
        return returnCode;
    } else {
        return 0;
    }
}

void hclog_init(FILE* stream) {
    if (0 == __hc_logfile) {
        __hc_logfile = stream;
    }
}

void hclog_close() {
    if((0 != __hc_logfile) && (stdout != __hc_logfile)) {
        fclose(__hc_logfile);
    }
}
