#include <stdio.h>

#define TABSTOP 8  // Default tab stop every 8 columns

void entab(int tabstop);

int main() {
    printf("Enter text (press Ctrl+D to end input):\n");
    entab(TABSTOP);
    return 0;
}

void entab(int tabstop) {
    int c, column = 0, space_count = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            // Increment space count and column position
            space_count++;
            column++;
        } else {
            // Replace spaces with tabs and spaces as needed
            while (space_count > 0) {
                if ((column - space_count) % tabstop == 0) {
                    putchar('\t');  // Insert a tab
                    space_count -= tabstop - ((column - space_count) % tabstop);
                } else {
                    putchar(' ');  // Insert a space
                    space_count--;
                }
            }

            // Print the non-space character
            putchar(c);

            // Reset column on newline, otherwise increment
            if (c == '\n') {
                column = 0;
            } else {
                column++;
            }
        }
    }

    // Handle trailing spaces
    while (space_count > 0) {
        if ((column - space_count) % tabstop == 0) {
            putchar('\t');
            space_count -= tabstop - ((column - space_count) % tabstop);
        } else {
            putchar(' ');
            space_count--;
        }
    }
}
