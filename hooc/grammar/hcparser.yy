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

%type<hooc::ast::Operator> operator
%type<hooc::ast::Expression> literal_expr
%type<hooc::ast::Expression> unary_expression
%type<hooc::ast::Expression> binary_expression
%type<hooc::ast::Expression> expr

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
        binary_expression { $$ = $1; }
        ;

    binary_expression:
        unary_expression operator unary_expression {
            $$ = driver.CreateBinaryExpression($1, $2, $3);
        }|
        binary_expression operator unary_expression {
            $$ = driver.CreateBinaryExpression($1, $2, $3);
        }

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