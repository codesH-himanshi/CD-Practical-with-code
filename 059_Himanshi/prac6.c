#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_NON_TERMINALS 26
#define MAX_PRODUCTIONS 50

// Structure to represent a production rule.
typedef struct {
    char nonTerminal;
    char productions[MAX_PRODUCTIONS][MAX_PRODUCTIONS]; // Array of production rules
    int numProductions;
} GrammarRule;

// Array to hold all the grammar rules
GrammarRule grammar[MAX_NON_TERMINALS];
int numGrammarRules = 0;

// Array to store the FIRST sets for each non-terminal
char firstSets[MAX_NON_TERMINALS][MAX_PRODUCTIONS];
int firstSetSizes[MAX_NON_TERMINALS];

// Function to find the index of a non-terminal in the grammar
int getNonTerminalIndex(char nt) {
    for (int i = 0; i < numGrammarRules; i++) {
        if (grammar[i].nonTerminal == nt) {
            return i;
        }
    }
    return -1;
}

// Function to check if a character is a terminal
int isTerminal(char c) {
    return (c >= 'a' && c <= 'z');
}

// Function to compute the FIRST set of a non-terminal
void computeFirstSet(char nonTerminal) {
    int index = getNonTerminalIndex(nonTerminal);
    if (index == -1) return; // Non-terminal not found

    // Iterate through all the productions of the non-terminal
    for (int i = 0; i < grammar[index].numProductions; i++) {
        char *production = grammar[index].productions[i];

        if (isTerminal(production[0])) {
            // If the production starts with a terminal, add it to the FIRST set
            if (!strchr(firstSets[index], production[0])) {
                firstSets[index][firstSetSizes[index]++] = production[0];
            }
        } else if (production[0] != 'e') {
            // If the production starts with a non-terminal, recursively compute its FIRST set
            int subIndex = getNonTerminalIndex(production[0]);
            if (subIndex != -1) {
                // Avoid circular calls to prevent infinite recursion
                if (firstSets[subIndex][0] == '\0') {
                    computeFirstSet(production[0]);
                }
                // Copy the FIRST set of the sub non-terminal into the current set
                for (int j = 0; j < firstSetSizes[subIndex]; j++) {
                    if (!strchr(firstSets[index], firstSets[subIndex][j])) {
                        firstSets[index][firstSetSizes[index]++] = firstSets[subIndex][j];
                    }
                }
            }
        }
    }
}

// Function to input grammar
void inputGrammar() {
    printf("Enter the number of grammar rules: ");
    scanf("%d", &numGrammarRules);

    // Read the production rules
    for (int i = 0; i < numGrammarRules; i++) {
        printf("Enter the non-terminal for rule %d: ", i + 1);
        scanf(" %c", &grammar[i].nonTerminal);
        
        printf("Enter the productions for %c (separate with '|'): ", grammar[i].nonTerminal);
        char productionLine[500];
        getchar(); // To capture the newline character
        fgets(productionLine, sizeof(productionLine), stdin);

        char *token = strtok(productionLine, "|");
        int prodCount = 0;
        
        // Split and store productions
        while (token != NULL) {
            strcpy(grammar[i].productions[prodCount++], token);
            token = strtok(NULL, "|");
        }
        
        grammar[i].numProductions = prodCount;
    }
}

// Function to print the FIRST sets
void printFirstSets() {
    printf("\nFIRST sets:\n");
    for (int i = 0; i < numGrammarRules; i++) {
        printf("FIRST(%c) = {", grammar[i].nonTerminal);
        for (int j = 0; j < firstSetSizes[i]; j++) {
            if (j > 0) printf(", ");
            printf("%c", firstSets[i][j]);
        }
        printf("}\n");
    }
}

int main() {
    // Initialize first sets sizes
    for (int i = 0; i < MAX_NON_TERMINALS; i++) {
        firstSetSizes[i] = 0;
    }

    // Input the grammar
    inputGrammar();

    // Compute FIRST sets for all non-terminals
    for (int i = 0; i < numGrammarRules; i++) {
        computeFirstSet(grammar[i].nonTerminal);
    }

    // Print the computed FIRST sets
    printFirstSets();

    return 0;
}
