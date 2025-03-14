#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

int getfloat(float *pn) {
    int c, sign;
    float power;

    while (isspace(c = getch()))  // Skip white space
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);  // Not a number
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int next = getch();
        if (!isdigit(next) && next != '.') {
            ungetch(next);  // Push back non-digit character
            ungetch(c);     // Push back '+' or '-'
            return 0;
        }
        c = next;  // Proceed with the next character
    }

    for (*pn = 0.0; isdigit(c); c = getch())  // Integer part
        *pn = 10.0 * *pn + (c - '0');

    if (c == '.') {  // Fractional part
        power = 1.0;
        while (isdigit(c = getch())) {
            *pn = 10.0 * *pn + (c - '0');
            power *= 10.0;
        }
        *pn /= power;
    }

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
    float num;
    int result;

    printf("Enter a floating-point number: ");
    result = getfloat(&num);

    if (result > 0)
        printf("You entered: %f\n", num);
    else if (result == 0)
        printf("Not a valid float.\n");
    else
        printf("End of input or error.\n");

    return 0;
}
