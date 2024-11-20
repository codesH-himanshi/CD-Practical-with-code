%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'

%%
input:
    | input expr '\n' { printf("Result: %d\n", $2); }
    ;

expr:
    expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            exit(1);
        } else {
            $$ = $1 / $3; 
        }
    }
    | expr '%' expr { 
        if ($3 == 0) {
            printf("Error: Division by zero\n");
            exit(1);
        } else {
            $$ = $1 % $3; 
        }
    }
    | '(' expr ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;

%%
int yylex() {
    int c;

    // Skip whitespace
    while ((c = getchar()) == ' ' || c == '\t');

    if (c == EOF) {
        return 0;
    }

    if (c >= '0' && c <= '9') {
        ungetc(c, stdin);
        scanf("%d", &yylval); // Read a number
        return NUMBER;
    }

    return c; // return operator or parenthesis
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expressions with *, /, and %% operators:\n");
    return yyparse();
}
