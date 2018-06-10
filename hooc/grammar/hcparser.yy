%{
#include <stdio.h>
extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern char* yytext;
void yyerror(const char* s);
%}

%require "3.0"
%debug
%skeleton "lalr1.cc"
%name-prefix "hooc"
%define parser_class_name {Parser}
%locations
%error-verbose

%token TOKEN_PUC_SEMICOLON
%token TOKEN_OPR_ADD
%token TOKEN_OPR_SUB
%token TOKEN_OPR_MUL
%token TOKEN_OPR_DIV
%token TOKEN_OPR_MOD
%token TOKEN_LITERAL_INT


%%
    prog: /* empty */
        |
        stmt_list
        ;

    stmt_list:
        stmt
        |
        stmt_list stmt
        ;

    stmt:
        base_stmt;

    base_stmt:
        expr TOKEN_PUC_SEMICOLON
        ;

    expr:
        binary_expr
        |
        base_expr
        ;

    binary_expr:
        base_expr operator expr
        ;

    base_expr:    
        literal_expr
        ;

    literal_expr:
        TOKEN_LITERAL_INT
        ;

    operator:   
        TOKEN_OPR_ADD
        | 
        TOKEN_OPR_SUB
        |   
        TOKEN_OPR_MUL
        | 
        TOKEN_OPR_DIV
        | 
        TOKEN_OPR_MOD 
        ;
%%