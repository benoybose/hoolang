%{

%}
%skeleton "lalr1.cc"
%require "3.0"
%debug
%define parser_class_name {Parser}

%define api.namespace {hooc}
%define api.value.type variant
%define parse.error verbose

%code requires {
    namespace hooc {
        class ParserDriver;
    }
}

%parse-param { ParserDriver &driver }
%code {
    #include "ParserDriver.hh"
    #undef yylex
    #define yylex driver.Scan
}

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