%{
    #include <stdio.h>
    #include "hcparser.h"

    extern int yylex();
    extern int yyparse();
    extern FILE* yyin;
    void yyerror(const char* s);
%}

%token TOKEN_OPR_ADD
%token TOKEN_OPR_SUB
%token TOKEN_OPR_MUL
%token TOKEN_OPR_DIV
%token TOKEN_OPR_MOD

%token TOKEN_LITERAL_INT


%%
    expr_binary:  expr
        |
        expr operator expr
        ;

    expr: literal
        ;

    literal: TOKEN_LITERAL_INT
        ;

    operator:   TOKEN_OPR_ADD
            | 
                TOKEN_OPR_SUB 
            |   
                TOKEN_OPR_MUL 
            | 
                TOKEN_OPR_DIV 
            | 
                TOKEN_OPR_MOD
            ;
        ;
%%