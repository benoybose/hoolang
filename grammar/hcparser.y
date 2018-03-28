%{
#include <stdio.h>
#include "nodes/hcliteral.h"
#include "nodes/hcoperator.h"
#include "nodes/hcbaseexpression.h"
#include "nodes/hcbinaryexpression.h"
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
    struct hc_node_operator* node_operator;
    struct hc_node_literal* node_literal;
    struct hc_node_base_expression* node_base_expression;
    struct hc_node_binary_expression* node_binary_expression;
}

%type<node_literal> literal
%type<node_operator> operator
%type<node_base_expression> base_expression
%type<node_binary_expression> binary_expression 

%%
    expression: 
        binary_expression { hclog_print("Expression: Binary Expression."); }
        |
        base_expression { hclog_print("Expression: Base Expression."); }
        ;

    binary_expression:
        base_expression operator base_expression {
            hclog_print("binary expression");
            $$ = hc_node_binary_expression_create((struct hc_node*) $1, 
                    $2, (struct hc_node*) $3);
        }
        |
        binary_expression operator base_expression {
            hclog_print("compound binary expression");
        };

    base_expression:    
        literal {
            hclog_print("base_expression: literal");
            $$ = hc_base_expression_create(HC_BASE_EXPRESSION_LITERAL, 
                    (struct hc_node*) $1); 
        };

    literal:
        TOKEN_LITERAL_INT { 
            hclog_print("literal: TOKEN_LITERAL_INT %s", yytext);
            $$ = hc_node_literal_create(yytext, HC_LITERAL_INT32); 
        };

    operator:   
        TOKEN_OPR_ADD { $$ = hc_node_operator_create(HC_OPERATOR_ADD); }
        | 
        TOKEN_OPR_SUB { $$ = hc_node_operator_create(HC_OPERATOR_SUB); }
        |   
        TOKEN_OPR_MUL { $$ = hc_node_operator_create(HC_OPERATOR_MUL); }
        | 
        TOKEN_OPR_DIV { $$ = hc_node_operator_create(HC_OPERATOR_DIV); }
        | 
        TOKEN_OPR_MOD { $$ = hc_node_operator_create(HC_OPERATOR_MOD); }
        ;
%%