#include <stdio.h>

int main() {
    int c;

    printf("Enter characters, and press Ctrl+D (or Ctrl+Z on Windows) to send EOF:\n");

    while (1) {
        printf("Type a character: ");
        c = getchar(); // Read a character

        if (c == EOF) {
            printf("\nYou entered EOF. The expression getchar() != EOF evaluates to: 0\n");
            break;
        } else {
            printf("You entered '%c'. The expression getchar() != EOF evaluates to: 1\n", c);
        }

        // Clear the newline from the buffer
        getchar(); 
    }

    return 0;
}
