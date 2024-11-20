#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 100
#define MAX_PROD_LENGTH 100

int isOperatorPrecedent(char grammar[MAX_PRODUCTIONS][MAX_PROD_LENGTH], int grammarCount) {
    for (int i = 0; i < grammarCount; i++) {
        char* arrowPos = strstr(grammar[i], "-->");
        if (arrowPos == NULL) continue;

        int lhsLen = arrowPos - grammar[i];
        char lhs[MAX_PROD_LENGTH];
        strncpy(lhs, grammar[i], lhsLen);
        lhs[lhsLen] = '\0';

        char rhs[MAX_PROD_LENGTH];
        strcpy(rhs, arrowPos + 3); // Skip "-->"

        char* part = strtok(rhs, "|");
        while (part != NULL) {
            if (strchr(part, 'e') != NULL) {
                return 0; 
            }

            char prevChar = '\0';
            for (int j = 0; part[j] != '\0'; j++) {
                char ch = part[j];
                if (isupper(ch)) { 
                    if (isupper(prevChar)) { 
                        return 0; 
                    }
                }
                prevChar = ch; 
            }
            part = strtok(NULL, "|"); 
        }
    }
    return 1; 
}

int main() {
    char grammar[MAX_PRODUCTIONS][MAX_PROD_LENGTH];
    int grammarCount = 0;

    printf("Enter grammar productions (type 'end' to finish):\n");

    while (1) {
        char line[MAX_PROD_LENGTH];
        fgets(line, sizeof(line), stdin);

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "end") == 0) {
            break;         }

        if (strstr(line, "-->") != NULL) {
            strcpy(grammar[grammarCount++], line); 
        } else {
            printf("Invalid production format. Please follow the rules.\n");
        }
    }

    if (isOperatorPrecedent(grammar, grammarCount)) {
        printf("The grammar is operator precedence.\n");
    } else {
        printf("The grammar is not operator precedence.\n");
    }

    return 0;
}
