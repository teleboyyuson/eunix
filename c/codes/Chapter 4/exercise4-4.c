#include <stdio.h>
#include <stdlib.h>  // For atof
#include <ctype.h>

#define MAXVAL 100  // Maximum stack depth
int sp = 0;         // Stack pointer
double val[MAXVAL]; // Stack

void push(double f);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

int main() {
    char input;
    double num;

    printf("Enter commands:\n");
    while (scanf(" %c", &input) != EOF) {
        switch (input) {
            case 'n':  // Push number
                scanf("%lf", &num);
                push(num);
                break;
            case 'p':  // Print top element
                print_top();
                break;
            case 'd':  // Duplicate top element
                duplicate_top();
                break;
            case 's':  // Swap top two elements
                swap_top();
                break;
            case 'c':  // Clear stack
                clear_stack();
                break;
            case 'q':  // Quit
                return 0;
            default:
                printf("Unknown command: %c\n", input);
                break;
        }
    }
    return 0;
}

/* Push a number onto the stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: Stack full\n");
}

/* Pop and return the top value */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: Stack empty\n");
        return 0.0;
    }
}

/* Print the top element without popping */
void print_top(void) {
    if (sp > 0)
        printf("Top element: %.8g\n", val[sp - 1]);
    else
        printf("Error: Stack empty\n");
}

/* Duplicate the top element */
void duplicate_top(void) {
    if (sp > 0 && sp < MAXVAL)
        push(val[sp - 1]);
    else
        printf("Error: Cannot duplicate\n");
}

/* Swap the top two elements */
void swap_top(void) {
    if (sp > 1) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("Error: Not enough elements to swap\n");
    }
}

/* Clear the stack */
void clear_stack(void) {
    sp = 0;
    printf("Stack cleared\n");
}
