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
    #include "Logger.hh"
    #undef yylex
    #define yylex driver.Scan
}

%code requires {
    #include "Operator.hh"
    #include "Expression.hh"
    #include <string>
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
%token<std::string> TOKEN_LITERAL_INT

%type<hooc::Operator> operator
%type<hooc::Expression> literal_expr
%type<hooc::Expression> unary_expression

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
        binary_expression
        ;

    binary_expression:
        unary_expression operator unary_expression {
            hooc::Logger::Info($1.getNodeTypeName());
            hooc::Logger::Info($2.getNodeTypeName());
            hooc::Logger::Info($3.getNodeTypeName());
        }|
        binary_expression operator unary_expression;

    unary_expression:
        literal_expr { $$ = $1; }
        ;

    literal_expr:
        TOKEN_LITERAL_INT { hooc::Logger::Info($1);
            $$ = driver.CreateLiteralExpression(hooc::LiteralType::IntegerLiteral, $1);
        };

    operator:   
        TOKEN_OPR_ADD { $$ = driver.CreateOperator('+'); }
        | 
        TOKEN_OPR_SUB { $$ = driver.CreateOperator('-'); }
        |   
        TOKEN_OPR_MUL { $$ = driver.CreateOperator('*'); }
        | 
        TOKEN_OPR_DIV { $$ = driver.CreateOperator('/'); }
        | 
        TOKEN_OPR_MOD { $$ = driver.CreateOperator('%'); }
        ;
%%