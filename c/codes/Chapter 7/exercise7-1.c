#include <stdio.h>
#include <stdlib.h>  // For atof
#include <math.h>    // For sin, exp, pow
#include <ctype.h>   // For isdigit

#define MAXVAL 100  // Maximum stack depth
#define MAXOP 100   // Maximum operand size
#define NUMBER '0'  // Signal that a number was found

int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    printf("RPN Calculator: Supports +, -, *, /, %%, sin, exp, pow\n");
    printf("Enter numbers and operators (Ctrl+D to exit)\n");

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
            case '%':  // Modulus using fmod()
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("Error: Modulo by zero\n");
                break;
            case 's':  // sin(x)
                push(sin(pop()));
                break;
            case 'e':  // exp(x)
                push(exp(pop()));
                break;
            case 'p':  // pow(x, y)
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 't':  // Print top element
                print_top();
                break;
            case 'd':  // Duplicate top element
                duplicate_top();
                break;
            case 'x':  // Swap top two elements
                swap_top();
                break;
            case 'c':  // Clear stack
                clear_stack();
                break;
            case '\n': // Print result
                printf("Result: %.8g\n", pop());
                break;
            default:
                printf("Error: Unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

/* Stack */
double val[MAXVAL]; // Value stack
int sp = 0;         // Next free stack position

/* push: push f onto stack */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("Error: Stack full, can't push %g\n", f);
}

/* pop: pop and return top value */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("Error: Stack empty\n");
        return 0.0;
    }
}

/* print_top: print the top element without popping */
void print_top(void) {
    if (sp > 0)
        printf("Top element: %.8g\n", val[sp - 1]);
    else
        printf("Error: Stack empty\n");
}

/* duplicate_top: duplicate the top element */
void duplicate_top(void) {
    if (sp > 0 && sp < MAXVAL)
        push(val[sp - 1]);
    else
        printf("Error: Cannot duplicate, stack empty or full\n");
}

/* swap_top: swap the top two elements */
void swap_top(void) {
    if (sp > 1) {
        double temp = val[sp - 1];
        val[sp - 1] = val[sp - 2];
        val[sp - 2] = temp;
    } else {
        printf("Error: Not enough elements to swap\n");
    }
}

/* clear_stack: clear the stack */
void clear_stack(void) {
    sp = 0;
    printf("Stack cleared\n");
}

/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while ((s[0] = c = getchar()) == ' ' || c == '\t') // Skip whitespace
        ;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && c != '-')  // Not a number
        return c;

    i = 0;
    if (c == '-') {  // Handle negative numbers
        int next = getchar();
        if (!isdigit(next) && next != '.') {
            ungetc(next, stdin);
            return c;
        }
        s[++i] = c = next;
    }

    if (isdigit(c))  // Collect integer part
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')  // Collect fraction part
        while (isdigit(s[++i] = c = getchar()))
            ;
    
    s[i] = '\0';
    if (c != EOF)
        ungetc(c, stdin);
    
    return NUMBER;
}
