#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000  // Maximum length of a line
#define LINES_PER_PAGE 50  // Number of lines per page

void print_file(FILE *fp, const char *filename) {
    char line[MAXLINE];
    int lineno = 0, page = 1;

    printf("\n========== %s (Page %d) ==========\n\n", filename, page);
    
    while (fgets(line, MAXLINE, fp)) {
        if (lineno >= LINES_PER_PAGE) {  
            // Start a new page
            page++;
            printf("\f");  // Form feed for a new page (may not work in all terminals)
            printf("\n========== %s (Page %d) ==========\n\n", filename, page);
            lineno = 0;
        }

        printf("%s", line);
        lineno++;
    }
    
    printf("\n========== End of %s ==========\n", filename);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 [file2 ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error: Cannot open file %s\n", argv[i]);
            continue;
        }

        print_file(fp, argv[i]);
        fclose(fp);
    }

    return 0;
}
