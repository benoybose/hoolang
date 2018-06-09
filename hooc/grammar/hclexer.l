%{
    #include<stdio.h>
    #include "hcparser.h"
    #include "hclogger.h"
%}

%option noyywrap

%%
";" { return TOKEN_PUC_SEMICOLON; }
[0-9]+  { return TOKEN_LITERAL_INT; }
"+" { return TOKEN_OPR_ADD; }
"-" { return TOKEN_OPR_SUB; }
"*" { return TOKEN_OPR_MUL; }
"/" { return TOKEN_OPR_DIV; }
"%" { return TOKEN_OPR_MOD; }
[ \r\n\t]+ /* Ignore white space */
%%

