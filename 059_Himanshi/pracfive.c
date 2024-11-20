#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int commonPrefixLength(char *str1, char *str2) {
    int i = 0;
    while (str1[i] && str2[i] && str1[i] == str2[i]) {
        i++;
    }
    return i;
}

void checkLeftFactoring(char *input) {
    char nonTerminal, alpha[MAX], betas[MAX][MAX];
    char *token;
    int i = 0, prefixLength = 0;
    int minPrefixLength = MAX;
    char prefix[MAX];

    nonTerminal = input[0]; 

    token = strtok(input + 3, "|"); 
    while (token != NULL) {
        strcpy(betas[i++], token);
        token = strtok(NULL, "|");
    }

    for (int k = 1; k < i; k++) {
        prefixLength = commonPrefixLength(betas[0], betas[k]);
        if (prefixLength < minPrefixLength) {
            minPrefixLength = prefixLength;
        }
    }

    if (minPrefixLength == 0) {
        printf("No Left Factoring\n");
        return;
    }

    strncpy(prefix, betas[0], minPrefixLength);
    prefix[minPrefixLength] = '\0';

    printf("Left Factoring Grammar Detected\n");
    printf("Corrected Grammar:\n");

    printf("%c --> %s%c'|", nonTerminal, prefix, nonTerminal);

    for (int k = 0; k < i; k++) {
        if (strncmp(betas[k], prefix, minPrefixLength) != 0) {
            printf("%s", betas[k]);
        }
    }
    printf("\n");

    printf("%c' --> ", nonTerminal);
    for (int k = 0; k < i; k++) {
        if (k > 0) printf("|");
        if (strlen(betas[k]) > minPrefixLength) {
            printf("%s", betas[k] + minPrefixLength);
        } else {
            printf("e"); // epsilon
        }
    }
    printf("\n");
}

int main() {
    char input[MAX];
    printf("Enter a production rule: ");
    fgets(input, MAX, stdin);


    input[strcspn(input, "\n")] = '\0';

    checkLeftFactoring(input);

    return 0;
}
