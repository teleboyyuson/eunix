#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 // Maximum input line size

// Function prototypes
int getLine(char line[], int maxline);
void copy(char to[], const char from[]);

int main(void) {
    int len;              // Current line length
    int max = 0;          // Maximum length seen so far
    char line[MAXLINE];   // Current input line
    char longest[MAXLINE]; // Longest line saved here

    // Read lines and track the longest
    while ((len = getLine(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }

    // Print the longest line if any
    if (max > 0) {
        printf("Longest line (%d characters):\n%s", max, longest);
    }

    return EXIT_SUCCESS; // Indicate successful execution
}

/**
 * Reads a line into 's', up to a maximum length 'lim'.
 * Returns the length of the line read.
 */
int getLine(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    if (c == '\n') {
        s[i++] = c; // Add newline character to the line
    }
    s[i] = '\0'; // Null-terminate the string
    return i;
}

 void copy(char to[], const char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }

 
}
