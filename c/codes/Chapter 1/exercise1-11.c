#include <stdio.h>
#include <ctype.h>

int main() {
    int c;
    int in_word = 0;
     
     // "WORD PRINTER"
     
    // Read characters until EOF

    printf("Insert a sentence to print each words {press Ctrl+D or Ctrl E (Windows) to end the execution}\n\n");
    while ((c = getchar()) != EOF) {
        if (isspace(c)) {
            // If it's a space and we're in a word, print a newline
            if (in_word) {
                putchar('\n');
                in_word = 0; // We're no longer in a word
            }
        } else {
            // If it's not a space, print the character
            putchar(c);
            in_word = 1; // We're in a word
        }
    }

    return 0;
}
