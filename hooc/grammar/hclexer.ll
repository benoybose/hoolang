%{
    #include "Parser.hh"
    typedef hooc::Parser::token token;
%}

%option debug
%option c++
%option nowarn

%%
";"     { return token::TOKEN_PUC_SEMICOLON; }
[0-9]+  { return token::TOKEN_LITERAL_INT; }
"+"     { return token::TOKEN_OPR_ADD; }
"-"     { return token::TOKEN_OPR_SUB; }
"*"     { return token::TOKEN_OPR_MUL; }
"/"     { return token::TOKEN_OPR_DIV; }
"%"     { return token::TOKEN_OPR_MOD; }
[ \r\n\t]+ /* Ignore white space */
%%

