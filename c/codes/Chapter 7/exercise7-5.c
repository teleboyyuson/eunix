#include <stdio.h>
#include <stdlib.h>  // For atof()
#include <ctype.h>   // For isdigit()
#include <math.h>    // For mathematical functions

#define MAXVAL 100   // Maximum depth of the stack

int sp = 0;          // Stack pointer
double val[MAXVAL];  // Value stack

// Function Prototypes
void push(double);
double pop(void);

int main() {
    char input[100];
    double operand;
    
    printf("Enter a postfix expression (CTRL+D to end):\n");

    while (scanf("%s", input) != EOF) {
        if (sscanf(input, "%lf", &operand) == 1) {
            // If input is a number, push it onto the stack
            push(operand);
        } else if (input[0] == '+') {
            push(pop() + pop());
        } else if (input[0] == '-') {
            double op2 = pop();
            push(pop() - op2);
        } else if (input[0] == '*') {
            push(pop() * pop());
        } else if (input[0] == '/') {
            double op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("Error: Division by zero\n");
        } else if (input[0] == '%') {
            int op2 = (int)pop();
            int op1 = (int)pop();
            if (op2 != 0)
                push(op1 % op2);
            else
                printf("Error: Modulo by zero\n");
        } else {
            printf("Error: Unknown command %s\n", input);
        }
    }

    printf("Result: %.8g\n", pop());
    return 0;
}

// Push function
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: Stack full, can't push %g\n", f);
}

// Pop function
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: Stack empty\n");
        return 0.0;
    }
}
