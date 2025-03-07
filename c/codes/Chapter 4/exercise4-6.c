#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100    // Max size of operand or operator
#define NUMBER '0'   // Signal that a number was found
#define VAR 'A'      // Signal that a variable was found
#define LASTVAR 'L'  // Special variable for last printed value
#define MAXVAL 100   // Maximum depth of val stack

int getop(char []);
void push(double);
double pop(void);

// Stack for operands
int sp = 0;
double val[MAXVAL];
double variables[26];  // 26 letter variables
double last_printed = 0.0;

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
            case '%':
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("Error: Modulo by zero.\n");
                break;
            case '=':  // Handle assignment: "5 a ="
                op2 = pop();
                if (islower(s[0]))  // Ensure valid variable name
                    variables[s[0] - 'a'] = op2;
                else
                    printf("Error: Invalid variable name.\n");
                break;
            case VAR:
                push(variables[s[0] - 'a']);
                break;
            case LASTVAR:
                push(last_printed);
                break;
            case '\n':
                last_printed = pop();
                printf("\t%.8g\n", last_printed);
                break;
            default:
                printf("Error: Unknown command %s\n", s);
                break;
        }
    }
    return 0;
}

// Stack operations
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

// Get the next operator or operand
int getop(char s[]) {
    int i = 0, c;

    while ((s[0] = c = getchar()) == ' ' || c == '\t');  // Skip whitespace
    s[1] = '\0';

    if (isalpha(c)) {  
        s[0] = c;
        s[1] = '\0';
        return VAR;
    }

    if (!isdigit(c) && c != '.' && c != '-' && c != '=') 
        return c;  // Not a number, operator, or assignment

    if (c == '=') {  
        if (isalpha(c = getchar())) {  
            s[0] = c;
            s[1] = '\0';
            return VAR;
        } else {
            if (c != EOF)
                ungetc(c, stdin);
            return '=';
        }
    }

    if (c == '-') {  // Check if it's a negative number
        if (isdigit(c = getchar()) || c == '.')
            s[++i] = c;
        else {
            if (c != EOF)
                ungetc(c, stdin);
            return '-';
        }
    }

    if (isdigit(c))  // Collect integer part
        while (isdigit(s[++i] = c = getchar()));

    if (c == '.')  // Collect fraction part
        while (isdigit(s[++i] = c = getchar()));

    s[i] = '\0';
    if (c != EOF)
        ungetc(c, stdin);
    
    return NUMBER;
}
