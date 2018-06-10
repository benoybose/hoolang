%{
#include <stdio.h>

#include "hcoperator.hh"
#include "hcexpr.h"
#include "hcliteralexpr.h"
#include "hcbinaryexpr.h"
#include "hcexprstmt.h"
#include "hcstmt.h"
#include "hcstmtlist.h"
#include "hcprog.h"
#include "hclogger.h"
#include "hcparser.h"

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
struct hc_node_prog* __hc_currrent_prog;
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
    hooc::Operator* node_operator;
    struct hc_node_literal_expr* node_literal;
    struct hc_node_expr* node_expr;
    struct hc_node_binary_expr* node_binary_expr;
    struct hc_node_stmt* node_stmt;
    struct hc_node_stmt_list* node_stmt_list;
}

%type<node_operator> operator
%type<node_expr> expr
%type<node_literal> literal_expr
%type<node_expr> base_expr
%type<node_binary_expr> binary_expr
%type<node_stmt> base_stmt
%type<node_stmt> stmt
%type<node_stmt_list> stmt_list;

%%
    prog: /* empty */
        |
        stmt_list {
            hclog_print("prog: stmt_list");
            if(0 != __hc_currrent_prog) {
                __hc_currrent_prog->stmt_list = $1;
                hclog_print("statement list assigned.");
            }
        };

    stmt_list:
        stmt {
            hclog_print("stmt_list: stmt");
            struct hc_node_stmt_list* list = hc_node_stmt_list_create();
            hc_node_stlt_list_add(list, $1);
            $$ = list;
        }
        |
        stmt_list stmt {
            hclog_print("stmt_list: stmt_list stmt");
            size_t stmt_count = hc_node_stlt_list_add($1, $2);
            hclog_print("stmt count: %u", stmt_count);
            $$ = $1;
        };

    stmt:
        base_stmt {
            hclog_print("stmt: base_stmt");
            $$ = $1;
        };

    base_stmt:
        expr TOKEN_PUC_SEMICOLON {
            hclog_print("basestmt: expr");
            $$ = (struct hc_node_stmt*) hc_node_expr_stmt_create($1);
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
            $$ = new hooc::Operator(hooc::OperatorType::HC_OPERATOR_ADD);
        }
        | 
        TOKEN_OPR_SUB { 
            hclog_print("operator: -");
            $$ = new hooc::Operator(hooc::OperatorType::HC_OPERATOR_SUB);
        }
        |   
        TOKEN_OPR_MUL { 
            hclog_print("operator: *");
            $$ = new hooc::Operator(hooc::OperatorType::HC_OPERATOR_MUL);
        }
        | 
        TOKEN_OPR_DIV {
            hclog_print("operator: /");
            $$ = new hooc::Operator(hooc::OperatorType::HC_OPERATOR_DIV);
        }
        | 
        TOKEN_OPR_MOD {
            hclog_print("operator: %");
            $$ = new hooc::Operator(hooc::OperatorType::HC_OPERATOR_MOD);
        };
%%