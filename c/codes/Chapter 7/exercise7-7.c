#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000  // Maximum line length

// Function to get a line of input
int get_line(char *line, int max, FILE *fp) {
    if (fgets(line, max, fp) != NULL) {
        return strlen(line);
    }
    return 0;
}

// Function to search for a pattern in a file
void search_in_file(const char *pattern, FILE *fp, const char *filename) {
    char line[MAXLINE];
    int lineno = 0;

    while (get_line(line, MAXLINE, fp) > 0) {
        lineno++;
        if (strstr(line, pattern) != NULL) {  // Check if pattern exists in line
            if (filename != NULL) {
                printf("%s:%d: %s", filename, lineno, line);  // Print filename and line number
            } else {
                printf("%d: %s", lineno, line);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s pattern [file...]\n", argv[0]);
        return 1;
    }

    char *pattern = argv[1];

    if (argc == 2) {
        // No files provided, read from standard input
        search_in_file(pattern, stdin, NULL);
    } else {
        // Loop through each file
        for (int i = 2; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[i]);
                continue;
            }
            search_in_file(pattern, fp, argv[i]);
            fclose(fp);
        }
    }
    return 0;
}
