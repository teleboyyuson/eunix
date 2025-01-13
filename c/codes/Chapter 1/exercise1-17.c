#include <stdio.h>
#define MAXLINE 1000  // Maximum input line size
#define THRESHOLD 80  // Threshold for line length

// Function to read a line of input
int getLine(char line[], int maxLine);

int main() {
    char line[MAXLINE];  // Current input line
    int len;             // Length of the current line

    printf("Enter lines of text (Ctrl+D to stop):\n");

    while ((len = getLine(line, MAXLINE)) > 0) {
        if (len > THRESHOLD) {
            printf("Long line (> %d chars): %s", THRESHOLD, line);
            // Ensure the line ends with a newline for proper display
            if (line[len - 1] != '\n') {
                printf("\n");
            }
        }
    }

    return 0;
}

// Reads a line into `line` and returns its length
int getLine(char line[], int maxLine) {
    int c, i;

    for (i = 0; i < maxLine - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i++] = c;  // Include the newline character
    }
    line[i] = '\0';  // Null-terminate the string

    return i;
}

