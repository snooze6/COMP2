%{
#include "simple.tab.h"
extern int line_number;
%}
%option noyywrap

%%
"float"         { printf("FROM FLEX FLOAT %s\n", yytext); return FLOAT;  }
"int"           { printf("FROM FLEX INT %s\n", yytext); return INT; }
[;] {  return *yytext; }
[_a-zA-Z][_a-zA-Z0-9]* { printf("FROM FLEX IDENTIFIER: %s\n", yytext); return IDENTIFIER; }
[ \t\r]+          /* eat up whitespace */
[\n] { line_number++; }
%%