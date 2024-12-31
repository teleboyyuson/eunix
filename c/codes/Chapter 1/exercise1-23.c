#include <stdio.h>
#include <stdbool.h>

void remove_comments() {
    int c, next;
    bool in_single_line_comment = false;
    bool in_multi_line_comment = false;
    bool in_string = false;
    bool in_char = false;

    while ((c = getchar()) != EOF) {
        if (in_single_line_comment) {
            // Handle single-line comments
            if (c == '\n') {
                in_single_line_comment = false;
                putchar(c); // Preserve the newline
            }
        } else if (in_multi_line_comment) {
            // Handle multi-line comments
            if (c == '*' && (next = getchar()) == '/') {
                in_multi_line_comment = false; // End of multi-line comment
            } else if (c == '*') {
                ungetc(next, stdin); // Lookahead for '/'
            }
        } else if (in_string) {
            // Handle string literals
            putchar(c);
            if (c == '\\') {
                // Escape sequence in string
                putchar(getchar());
            } else if (c == '"') {
                in_string = false; // End of string literal
            }
        } else if (in_char) {
            // Handle character constants
            putchar(c);
            if (c == '\\') {
                // Escape sequence in char
                putchar(getchar());
            } else if (c == '\'') {
                in_char = false; // End of character constant
            }
        } else {
            // Detect comments or handle regular code
            if (c == '/') {
                next = getchar();
                if (next == '/') {
                    in_single_line_comment = true; // Start of single-line comment
                } else if (next == '*') {
                    in_multi_line_comment = true; // Start of multi-line comment
                } else {
                    putchar(c);
                    ungetc(next, stdin); // Not a comment, put the next char back
                }
            } else {
                putchar(c);
                if (c == '"') {
                    in_string = true; // Start of string literal
                } else if (c == '\'') {
                    in_char = true; // Start of character constant
                }
            }
        }
    }
}

int main() {
    printf("Enter a C program (Ctrl+D to end input):\n");
    remove_comments();
    return 0;
}
