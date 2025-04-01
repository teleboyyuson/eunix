#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSTACK 100

int stack[MAXSTACK];
int sp = 0;

void push(int value) {
    if (sp < MAXSTACK) {
        stack[sp++] = value;
    } else {
        printf("Error: Stack full\n");
    }
}

int pop(void) {
    if (sp > 0) {
        return stack[--sp];
    } else {
        printf("Error: Stack empty\n");
        return 0;
    }
}

int is_number(const char *s) {
    while (*s) {
        if (!isdigit(*s) && *s != '-') {
            return 0;
        }
        s++;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    int i, op1, op2;

    if (argc < 2) {
        printf("Usage: expr <reverse Polish expression>\n");
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (is_number(argv[i])) {
            push(atoi(argv[i]));
        } else if (*argv[i] == '+' || *argv[i] == '-' || *argv[i] == '*' || *argv[i] == '/') {
            if (sp < 2) {
                printf("Error: Not enough operands\n");
                return 1;
            }
            op2 = pop();
            op1 = pop();
            switch (*argv[i]) {
                case '+': push(op1 + op2); break;
                case '-': push(op1 - op2); break;
                case '*': push(op1 * op2); break;
                case '/':
                    if (op2 != 0) {
                        push(op1 / op2);
                    } else {
                        printf("Error: Division by zero\n");
                        return 1;
                    }
                    break;
            }
        } else {
            printf("Error: Unknown operator %s\n", argv[i]);
            return 1;
        }
    }

    if (sp == 1) {
        printf("Result: %d\n", pop());
    } else {
        printf("Error: Invalid expression\n");
    }

    return 0;
}
