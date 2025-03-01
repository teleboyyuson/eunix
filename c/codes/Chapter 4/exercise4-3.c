#include <stdio.h>
#include <stdlib.h>  // For atof
#include <ctype.h>
#include <math.h>

#define MAXOP 100   // Max size of operand/operator
#define NUMBER '0'  // Signal that a number was found

int getop(char []);
void push(double);
double pop(void);

/* Reverse Polish Calculator */
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
                    printf("Error: Division by zero\n");
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2)); // Handles floating-point modulus
                else
                    printf("Error: Modulo by zero\n");
                break;
            case '\n':
                printf("Result: %.8g\n", pop());
                break;
            default:
                printf("Error: Unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

#define MAXVAL 100  // Max depth of val stack
int sp = 0;         // Next free stack position
double val[MAXVAL]; // Value stack

/* push: push f onto value stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: Stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: Stack empty\n");
        return 0.0;
    }
}

#include <stdio.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t') // Skip whitespace
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-' && c != '+') // Not a number
        return c;
    i = 0;
    if (c == '-' || c == '+') {  // Handle negative numbers
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);
            return c;  // Just return '+' or '-'
        }
        s[++i] = c = next;
    }
    if (isdigit(c))  // Collect integer part
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')  // Collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
