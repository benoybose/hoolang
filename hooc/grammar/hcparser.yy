%{

%}
%skeleton "lalr1.cc"
%require "3.0"
%debug
%define parser_class_name {Parser}

%define api.namespace {hooc}
%define api.value.type variant
%define parse.error verbose
%parse-param { ParserDriver &driver }

%code {
    #include "ParserDriver.hh"
    #undef yylex
    #define yylex driver.Scan
}

%code requires {
    #include "Operator.hh"
    namespace hooc {
        class ParserDriver;
    }

}

%token TOKEN_PUC_SEMICOLON
%token<hooc::Operator> TOKEN_OPR_ADD
%token<hooc::Operator> TOKEN_OPR_SUB
%token<hooc::Operator> TOKEN_OPR_MUL
%token<hooc::Operator> TOKEN_OPR_DIV
%token<hooc::Operator> TOKEN_OPR_MOD
%token TOKEN_LITERAL_INT

%type<hooc::Operator> operator

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