%option noyywrap
%%
boolean|float|int|if|char printf("keywords");
[0-9][0-9]* printf("constants");
[a-zA-Z][a-zA-Z0-9]* printf("identifiers");
%%

int main()
{

	yylex();

}
