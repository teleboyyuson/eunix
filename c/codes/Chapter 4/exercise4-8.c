#include <stdio.h>

int buf = 0;        // Single-character buffer
int buf_full = 0;   // Flag: 1 if buffer is full, 0 otherwise

int getch(void);     // Get a (possibly pushed-back) character
void ungetch(int c); // Push a character back on input

int main() {
    int c;

    printf("Enter a character: ");
    c = getch();  // Read a character from input
    printf("You entered: %c\n", c);

    ungetch(c);   // Push it back
    printf("Character pushed back!\n");

    c = getch();  // Read it again
    printf("Read back: %c\n", c);

    return 0;
}

// Get a (possibly pushed-back) character
int getch(void) {
    if (buf_full) {  // If buffer has a character, return it
        buf_full = 0;
        return buf;
    } else {
        return getchar();
    }
}

// Push a character back onto the input buffer
void ungetch(int c) {
    if (buf_full)
        printf("ungetch: buffer already full\n");
    else {
        buf = c;
        buf_full = 1;
    }
}
