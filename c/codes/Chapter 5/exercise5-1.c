#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()))  // Skip white space
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);  // Not a number
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int next = getch();
        if (!isdigit(next)) {  
            ungetch(next);  // Push back non-digit character
            ungetch(c);     // Push back '+' or '-'
            return 0;
        }
        c = next;  // Proceed with the next character
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    
    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

#define BUFSIZE 100

char buf[BUFSIZE];  // Buffer for ungetch
int bufp = 0;       // Next free position in buf

int getch(void) {   // Get a (possibly pushed-back) character
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { // Push character back on input
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main() {
    int num;
    int result;

    printf("Enter a number: ");
    result = getint(&num);

    if (result > 0)
        printf("You entered: %d\n", num);
    else if (result == 0)
        printf("Not a valid integer.\n");
    else
        printf("End of input or error.\n");

    return 0;
}
