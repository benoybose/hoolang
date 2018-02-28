%{
#include <stdio.h>
#include "literaltype.h"
#include "hcparser.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
void yyerror(const char* s);
%}

%token TOKEN_OPR_ADD
%token TOKEN_OPR_SUB
%token TOKEN_OPR_MUL
%token TOKEN_OPR_DIV
%token TOKEN_OPR_MOD
%token TOKEN_LITERAL_INT

%union {
    struct hclieral_node* liternalnode;
}

%type<liternalnode> literal

%%
    expr_binary: expr operator expr
        ;

    expr: literal   {
                        printf("literal expression found.");
                    }
        ;

    literal: TOKEN_LITERAL_INT { $$ = hcliteral_create(
                                            yytext, 
                                            LITERAL_TYPE_INT); 
                                }
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