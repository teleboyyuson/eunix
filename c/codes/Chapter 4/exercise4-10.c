#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 100  // Max input line size
#define MAXOP 100    // Max size of operand or operator
#define NUMBER '0'   // Signal that a number was found

int getop(char []);
void push(double);
double pop(void);

char line[MAXLINE];   // Input line storage
int line_index = 0;   // Current position in line

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while (1) {
        printf("Enter an expression: ");
        
        if (!fgets(line, MAXLINE, stdin)) // Read a new line, check for EOF
            break;
        line_index = 0; // Reset index for new line

        while ((type = getop(s)) != '\n' && type != EOF) {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("Error: Division by zero.\n");
                    break;
                default:
                    printf("Error: Unknown command %s\n", s);
                    break;
            }
        }
        
        // Print result when newline is encountered
        if (type == '\n') 
            printf("\t%.8g\n", pop());
    }

    return 0;
}

// Read next operator or operand from line
int getop(char s[]) {
    int i = 0, c;

    // Skip spaces
    while ((s[0] = c = line[line_index++]) == ' ' || c == '\t');

    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-') // Not a number
        return c;

    if (c == '-') { // Check for negative number
        if (isdigit(line[line_index]) || line[line_index] == '.') 
            s[++i] = c = line[line_index++];
        else
            return '-';
    }

    if (isdigit(c)) // Collect integer part
        while (isdigit(s[++i] = c = line[line_index++]));

    if (c == '.') // Collect fraction part
        while (isdigit(s[++i] = c = line[line_index++]));

    s[i] = '\0';
    line_index--; // Push back last read character

    return NUMBER;
}

// Stack functions
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: Stack full, cannot push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: Stack empty\n");
        return 0.0;
    }
}
