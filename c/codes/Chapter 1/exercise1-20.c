#include <stdio.h>

#define TAB_WIDTH 8 // Symbolic constant for tab stops

int main() {
    int c;
    int pos = 0; // Current column position

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            // Print debug info to stderr
            fprintf(stderr, "[TAB detected at pos %d]\n", pos);

            // Calculate spaces needed to reach the next tab stop
            int spaces = TAB_WIDTH - (pos % TAB_WIDTH);
            for (int i = 0; i < spaces; i++) {
                putchar(' ');
                pos++;
            }
        } else {
            putchar(c);
            pos++;

            // Reset position on a newline
            if (c == '\n') {
                pos = 0;
            }
        }
    }

    return 0;
}

//To execute this program:
// 1. Type a command on the terminal: echo -e {[Insert text]} | ./input.txt
//2. Execute the program file together 