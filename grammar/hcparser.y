%{
#include <stdio.h>
#include "hcliteral.h"
#include "hclogger.h"
#include "hcexpr.h"
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
    int operator_type;
    struct hc_node_literal* liternalnode;
    struct hc_node_expr* exprnode;
    struct hc_node_expr_binary* binaryexprnode;
}

%type<liternalnode> literal
%type<operator_type> operator
%type<exprnode> base_expression
%type<binaryexprnode> binary_expression 

%%
    binary_expression:  
        base_expression operator base_expression {
            hclog_print("binary expression");
        }
        |
        binary_expression operator base_expression {
            hclog_print("compound binary expression");
        };

    base_expression:    
        literal {
            hclog_print("base_expression: literal");
            $$ = hc_node_expr_create(EXPR_TYPE_LITERAL, $1); 
        };

    literal:
        TOKEN_LITERAL_INT { 
            hclog_print("literal: TOKEN_LITERAL_INT %s", yytext);
            $$ = hc_node_literal_create(yytext, LITERAL_TYPE_INT); 
        };

    operator:   
        TOKEN_OPR_ADD { $$ = OPERATOR_ADD; }
        | 
            TOKEN_OPR_SUB { $$ = OPERATOR_SUB; }
        |   
            TOKEN_OPR_MUL { $$ = OPERATOR_MUL; }
        | 
            TOKEN_OPR_DIV { $$ = OPERATOR_DIV; }
        | 
            TOKEN_OPR_MOD { $$ = OPERATOR_MOD; }
        ;
%%