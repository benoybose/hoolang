#include <stdio.h>
#include "hclexer.h"
#include "hcparser.h"

extern int yyparse();

int main() {
    yyin = stdin;
    do {
        yyparse();
    } while(!feof(yyin));
    return 0;
}

void yyerror(const char* message) {
    printf("Syntax error: %s.\r\n", message);
}