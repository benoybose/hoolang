#include <stdio.h>
#include "hclexer.h"
#include "hcparser.h"
#include "hclogger.h"

extern int yyparse();

int main() {
    yyin = stdin;
    hclog_init(stdout);
    do {
        yyparse();
    } while(!feof(yyin));
    hclog_close();
    return 0;
}

void yyerror(const char* message) {
    printf("Syntax error: %s.\r\n", message);
}