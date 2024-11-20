#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Production structure
typedef struct {
    char lhs;               // Left-hand side of the production
    char rhs[MAX];          // Right-hand side of the production
} Production;

Production productions[MAX];
int prod_count = 0;

// Function prototypes
void add_production(char lhs, const char *rhs);
void display_productions();
int is_terminal(char ch);
int shift_reduce_parse(char *input);

int main() {
    char input[MAX];
    int result;

    printf("Enter the productions (use '|' for multiple productions, enter 'END' to stop):\n");

    // Reading productions
    char line[MAX];
    while (1) {
        printf("Production %d: ", prod_count + 1);
        fgets(line, sizeof(line), stdin);
        
        // Remove newline character
        line[strcspn(line, "\n")] = 0;

        // Stop on "END"
        if (strcmp(line, "END") == 0) {
            break;
        }

        char *token = strtok(line, "-->");
        char lhs = token[0];
        
        token = strtok(NULL, "-->");
        char *rhs = strtok(token, "|");
        
        // Add each alternative production
        while (rhs != NULL) {
            add_production(lhs, rhs);
            rhs = strtok(NULL, "|");
        }
    }

    // Display the grammar
    printf("\nGrammar Productions:\n");
    display_productions();

    // Input string for parsing
    printf("\nEnter input string to parse: ");
    scanf("%s", input);

    // Parse the input string
    result = shift_reduce_parse(input);

    // Result
    if (result == 1) {
        printf("\nThe string is accepted.\n");
    } else {
        printf("\nThe string is not accepted.\n");
    }

    return 0;
}

// Add a production to the grammar
void add_production(char lhs, const char *rhs) {
    productions[prod_count].lhs = lhs;
    strcpy(productions[prod_count].rhs, rhs);
    prod_count++;
}

// Display productions
void display_productions() {
    for (int i = 0; i < prod_count; i++) {
        printf("%c --> %s\n", productions[i].lhs, productions[i].rhs);
    }
}

// Check if a character is a terminal
int is_terminal(char ch) {
    return islower(ch);
}

// Shift-Reduce Parsing
int shift_reduce_parse(char *input) {
    char stack[MAX] = "";
    char action[MAX];
    int i = 0, j = 0;

    printf("\nParsing Steps:\n");
    printf("Stack\tInput\tAction\n");
    printf("-----\t-----\t------\n");

    while (1) {
        // Shift action
        stack[j++] = input[i++];
        stack[j] = '\0';
        printf("%-5s\t%-5s\tShift\n", stack, input + i);

        // Reduce actions
        int reduced;
        do {
            reduced = 0;
            for (int k = 0; k < prod_count; k++) {
                int len = strlen(productions[k].rhs);
                if (j >= len && strcmp(&stack[j - len], productions[k].rhs) == 0) {
                    // Perform the reduction
                    j -= len;
                    stack[j++] = productions[k].lhs;
                    stack[j] = '\0';
                    reduced = 1;
                    printf("%-5s\t%-5s\tReduce by %c --> %s\n", stack, input + i, productions[k].lhs, productions[k].rhs);
                }
            }
        } while (reduced);

        // Check if stack has the start symbol and input is exhausted
        if (j == 1 && stack[0] == productions[0].lhs && input[i] == '\0') {
            return 1; // Accepted
        }

        // Check for parse failure
        if (input[i] == '\0' && j != 1) {
            return 0; // Not accepted
        }
    }
}
