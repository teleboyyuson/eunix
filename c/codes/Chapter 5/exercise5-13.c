#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NLINES 10
#define MAXLINE 1000

char *alloc(int n);
void free_allocated_lines(char *lines[], int n);

int main(int argc, char *argv[]) {
    int nlines = DEFAULT_NLINES;
    char *line_buffer[MAXLINE];
    char line[MAXLINE];
    int line_count = 0;

    // Parse the optional argument "-n"
    if (argc == 2 && argv[1][0] == '-') {
        nlines = atoi(&argv[1][1]);
        if (nlines <= 0) {
            fprintf(stderr, "Invalid line count: %d\n", nlines);
            return 1;
        }
    }

    // Dynamically allocate storage for lines
    while (fgets(line, MAXLINE, stdin)) {
        char *line_copy = alloc(strlen(line) + 1);
        if (line_copy == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            return 1;
        }
        strcpy(line_copy, line);

        // Store line in the circular buffer
        line_buffer[line_count % nlines] = line_copy;
        line_count++;
    }

    // Determine starting point for printing
    int start = (line_count >= nlines) ? line_count % nlines : 0;
    int count = (line_count >= nlines) ? nlines : line_count;

    // Print the last `nlines` lines
    for (int i = 0; i < count; i++) {
        printf("%s", line_buffer[(start + i) % nlines]);
    }

    // Free allocated memory
    free_allocated_lines(line_buffer, count);

    return 0;
}

char *alloc(int n) {
    return (char *)malloc(n);
}

void free_allocated_lines(char *lines[], int n) {
    for (int i = 0; i < n; i++) {
        free(lines[i]);
    }
}
