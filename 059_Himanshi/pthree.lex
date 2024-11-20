%{
#include "y.tab.h"
%}

%%

[0-9]+              { yylval = atoi(yytext); return NUMBER; }
[ \t\n]             { /* ignore whitespace */ }
"+"                 { return '+'; }
"-"                 { return '-'; }
"*"                 { return '*'; }
"/"                 { return '/'; }
"%"                 { return '%'; }
"("                 { return '('; }
")"                 { return ')'; }

.                   { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
