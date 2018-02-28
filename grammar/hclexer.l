%{
    #include<stdio.h>
    #include "literaltype.h"
    #include "hcparser.h"
%}

%option noyywrap

%%
[0-9]+  { printf("Number: %s", yytext); return TOKEN_LITERAL_INT; }
"+" { return TOKEN_OPR_ADD; }
"_" { return TOKEN_OPR_SUB; }
"*" { return TOKEN_OPR_MUL; }
"/" { return TOKEN_OPR_DIV; }
"%" { return TOKEN_OPR_MOD; }
%%

