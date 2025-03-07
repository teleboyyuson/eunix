#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100    // Max size of operand or operator
#define NUMBER '0'   // Signal that a number was found

int getop(char []);
void push(double);
double pop(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
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
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("Error: Unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

// Read next operator or numeric operand, without ungetch
int getop(char s[]) {
    static int buffered_char = 0; // Holds pushed-back character
    int i = 0, c;

    // Use buffered character if available; otherwise, read from input
    if (buffered_char) {
        c = buffered_char;
        buffered_char = 0;
    } else {
        c = getchar();
    }

    // Skip spaces and tabs
    while (c == ' ' || c == '\t')
        c = getchar();

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-') // Not a number
        return c;

    if (c == '-') { // Handle negative numbers
        int next = getchar();
        if (!isdigit(next) && next != '.') {
            buffered_char = next; // Push back if not a number
            return '-';
        }
        s[++i] = c = next;
    }

    if (isdigit(c)) // Collect integer part
        while (isdigit(s[++i] = c = getchar()));

    if (c == '.') // Collect fraction part
        while (isdigit(s[++i] = c = getchar()));

    s[i] = '\0';

    if (c != EOF)
        buffered_char = c; // Store unread character

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
