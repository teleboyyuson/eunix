#include <stdio.h>

/* Function to convert uppercase letters to lowercase using conditional expression */
char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

int main() {
    char ch;
    printf("Enter a character: ");
    scanf(" %c", &ch);

    char result = lower(ch);
    printf("Lowercase: %c\n", result);

    return 0;
}
