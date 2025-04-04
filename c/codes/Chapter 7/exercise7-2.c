#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 80  // Maximum length before breaking line

void print_visible(char c);
void print_non_graphic(char c);

int main() {
    int c, col = 0;

    while ((c = getchar()) != EOF) {
        if (isprint(c)) {
            print_visible(c);
        } else {
            print_non_graphic(c);
        }

        col++;
        if (col >= MAX_LINE_LENGTH) {
            putchar('\n');
            col = 0;
        }
    }
    return 0;
}

void print_visible(char c) {
    putchar(c);
}

void print_non_graphic(char c) {
    printf("\\x%02X", (unsigned char)c);  // Print non-graphic as hex
}
