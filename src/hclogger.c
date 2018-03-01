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
