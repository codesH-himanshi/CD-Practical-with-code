#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 100

void checkLeftRecursion(char* input) {
    char nonTerminal = input[0]; 
    char alpha[MAX], beta[MAX];  
    char* production = strstr(input, "-->") + 3; 
    char *token = strtok(production, "|");
    bool hasLeftRecursion = false;
    int alphaCount = 0, betaCount = 0;

    while (token != NULL) {
        if (token[0] == nonTerminal) {
            hasLeftRecursion = true;
            strcpy(alpha + alphaCount, token + 1); 
            alphaCount += strlen(token) - 1;
            strcat(alpha, "|");
        } else {
            strcpy(beta + betaCount, token); 
            betaCount += strlen(token);
            strcat(beta, "|");
        }
        token = strtok(NULL, "|"); 
    }
    
    if (betaCount > 0) beta[betaCount - 1] = '\0';
    if (alphaCount > 0) alpha[alphaCount - 1] = '\0';

    if (hasLeftRecursion) {
        printf("Left Recursive Grammar\n");
        printf("%c --> %s%c'\n", nonTerminal, beta, nonTerminal);
        printf("%c' --> %s%c' | e\n", nonTerminal, alpha, nonTerminal);
    } else {
        printf("No Left Recursion present.\n");
    }
}

int main() {
    char input[MAX];

    printf("Enter the production rule: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0; 

    checkLeftRecursion(input);

    return 0;
}
