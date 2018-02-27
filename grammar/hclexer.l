%{
    #include<stdio.h>
%}

%option noyywrap

%%
[0-9]+  { printf("Number: %s", yytext); }
"+" { printf("+ operator"); }
"_" { printf("- operator"); }
"*" { printf("* operator"); }
"/" { printf("/ operator"); }
"%" { printf("%% operator"); }
%%

