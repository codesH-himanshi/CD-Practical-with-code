%{
#include <stdio.h>
#include <string.h>

#define keyword_count 10
char keywords[keyword_count][10] = {
    "void", "int", "float", "char", "double", "return", "if", "else", "for", "while"
};

int is_keyword(char* str) {
for (int i = 0; i < keyword_count; i++) {
if (strcmp(str, keywords[i]) == 0) {
return 1;
}
}
return 0;
}
%}

%option noyywrap

%%

[ \t\n]+           
"void"|"int"|"float"|"char"|"double"|"return"|"if"|"else"|"for"|"while" { 
printf("Keyword: %s\n", yytext); 
}
[a-zA-Z_][a-zA-Z0-9_]*     {
if (is_keyword(yytext)) {
printf("Keyword: %s\n", yytext);
} else {
printf("Valid Identifier: %s\n", yytext);
}
}
.                           { printf("Neither a keyword nor a valid identifier: %s\n", yytext); }
%%

int main() {
printf("Enter a string: ");
yylex(); 
return 0;
}
