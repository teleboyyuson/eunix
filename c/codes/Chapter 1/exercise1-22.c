#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 // Maximum input line length

void fold_line(char line[], int n);

int main() {
    char line[MAXLINE];
    int n;

    printf("Enter the column width to fold lines: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid column width.\n");
        return 1;
    }
    getchar(); // Consume newline left in the buffer

    printf("Enter text (Ctrl+D to end input):\n");
    while (fgets(line, MAXLINE, stdin)) {
        fold_line(line, n);
    }

    return 0;
}

void fold_line(char line[], int n) {
    int len = strlen(line);
    int start = 0; // Start index of the current line

    while (start < len) {
        int end = start + n;
        if (end >= len) { // Last segment of the line
            printf("%s", &line[start]);
            break;
        }

        int fold_at = end;
        while (fold_at > start && line[fold_at] != ' ' && line[fold_at] != '\t') {
            fold_at--;
        }

        if (fold_at == start) { // No blank or tab found in the segment
            fold_at = end; // Break at the maximum column width
        }

        for (int i = start; i < fold_at; i++) {
            putchar(line[i]);
        }
        putchar('\n'); // Insert a newline at the break

        while (fold_at < len && (line[fold_at] == ' ' || line[fold_at] == '\t')) {
            fold_at++; // Skip over blanks and tabs
        }

        start = fold_at;
    }
}
