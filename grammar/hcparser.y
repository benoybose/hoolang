%{
#include <stdio.h>

#include "nodes/hcoperator.h"
#include "nodes/hcexpr.h"
#include "nodes/hcliteralexpr.h"
#include "nodes/hcbinaryexpr.h"
#include "hclogger.h"
#include "hcparser.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
void yyerror(const char* s);
%}

%token TOKEN_PUC_SEMICOLON
%token TOKEN_OPR_ADD
%token TOKEN_OPR_SUB
%token TOKEN_OPR_MUL
%token TOKEN_OPR_DIV
%token TOKEN_OPR_MOD
%token TOKEN_LITERAL_INT

%union {
    struct hc_node_operator* node_operator;
    struct hc_node_literal_expr* node_literal;
    struct hc_node_expr* node_expr;
    struct hc_node_binary_expr* node_binary_expr;
}

%type<node_operator> operator
%type<node_expr> expr
%type<node_literal> literal_expr
%type<node_expr> base_expr
%type<node_binary_expr> binary_expr

%%
    prog: /* empty */
        |
        stmt_list {
            hclog_print("prog: stmt_list");
        };

    stmt_list:
        stmt {
            hclog_print("stmt_list: stmt");
        }
        |
        stmt_list stmt {
            hclog_print("stmt_list: stmt_list stmt");
        };

    stmt:
        base_stmt {
            hclog_print("stmt: base_stmt");
        };

    base_stmt:
        expr TOKEN_PUC_SEMICOLON {
            hclog_print("basestmt: expr");
        };

    expr:
        binary_expr { 
            hclog_print("expr: binary_expr");
            $$ = (struct hc_node_expr*) $1;
        }
        |
        base_expr { 
            hclog_print("expr: base_expr");
            $$ = $1;
        };

    binary_expr:
        base_expr operator expr {
            $$ = hc_node_binary_expr_create($1, $2, $3);
        };

    base_expr:    
        literal_expr {
            hclog_print("base_expr: literal");
            $$ = (struct hc_node_expr*) $1;
        };

    literal_expr:
        TOKEN_LITERAL_INT { 
            hclog_print("literal: TOKEN_LITERAL_INT %s", yytext);
            $$ = hc_node_literal_expr_create(yytext, HC_LITERAL_INT32); 
        };

    operator:   
        TOKEN_OPR_ADD {
            hclog_print("operator: +");
            $$ = hc_node_operator_create(HC_OPERATOR_ADD); 
        }
        | 
        TOKEN_OPR_SUB { 
            hclog_print("operator: -");
            $$ = hc_node_operator_create(HC_OPERATOR_SUB); 
        }
        |   
        TOKEN_OPR_MUL { 
            hclog_print("operator: *");
            $$ = hc_node_operator_create(HC_OPERATOR_MUL); 
        }
        | 
        TOKEN_OPR_DIV {
            hclog_print("operator: /");
            $$ = hc_node_operator_create(HC_OPERATOR_DIV); 
        }
        | 
        TOKEN_OPR_MOD {
            hclog_print("operator: %");
            $$ = hc_node_operator_create(HC_OPERATOR_MOD); 
        };
%%