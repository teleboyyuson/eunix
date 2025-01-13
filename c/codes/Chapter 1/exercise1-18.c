#include <stdio.h>

#define MAXLINE 1000  // Maximum input line size

int getLine(char line[], int maxline);
void removeTrailingBlanks(char line[]);

int main() {
    char line[MAXLINE];  // Current input line

    printf("Enter lines of text (Ctrl+D to stop):\n");
    while (getLine(line, MAXLINE) > 0) {
        removeTrailingBlanks(line);
        if (line[0] != '\0') {  // Print non-blank lines only
            printf("%s\n", line);
        }
    }

    return 0;
}

// Reads a line into s, returns its length
int getLine(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

// Removes trailing blanks and tabs from a line
void removeTrailingBlanks(char line[]) {
    int i = 0;

    // Find the end of the line
    while (line[i] != '\0') {
        i++;
    }

    // Move backward to remove trailing blanks and tabs
    i--;  // Start just before the null character
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) {
        i--;
    }

    line[i + 1] = '\0';  // Terminate the string
}
