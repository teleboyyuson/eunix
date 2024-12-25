#include <stdio.h>
#define MAXLINE 1000  // Maximum input line size

int getLine(char line[], int maxline);

int main() {
    char line[MAXLINE]; // Current input line
    int len;            // Length of the current line

    printf("Enter lines of text (Ctrl+D to stop):\n");
    while ((len = getLine(line, MAXLINE)) > 0) {
        if (len > 80) { // Check if the line length exceeds 80
            printf("Long line (%d characters): %s", len, line);
        }
    }
    return 0;
}

// Function to read a line into 's' and return its length
int getLine(char s[], int lim) {
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = c; // Include newline character
    }
    s[i] = '\0'; // Null-terminate the string
    return i;    // Return the length of the line
}