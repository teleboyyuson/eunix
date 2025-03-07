#include <stdio.h>
#include <string.h>

#define BUFSIZE 100  // Buffer size for ungetch

char buf[BUFSIZE];  // Buffer for ungetch
int bufp = 0;       // Next free position in buf

int getch(void);     // Get a (possibly pushed back) character
void ungetch(int c); // Push character back on input
void ungets(char s[]); // Push entire string back on input

int main() {
    char test[] = "hello";
    
    printf("Pushing back: %s\n", test);
    ungets(test); // Push "hello" back onto input

    printf("Reading back: ");
    int c;
    while ((c = getch()) != EOF) {
        putchar(c);
    }
    
    printf("\n");
    return 0;
}

// Push an entire string onto the input buffer
void ungets(char s[]) {
    int len = strlen(s);
    while (len > 0) {
        ungetch(s[--len]); // Push back in reverse order
    }
}

// Get a (possibly pushed-back) character
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Push a character back onto the buffer
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
