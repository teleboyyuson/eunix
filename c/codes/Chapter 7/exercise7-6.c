#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000  // Maximum line length

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    FILE *fp1 = fopen(argv[1], "r");
    FILE *fp2 = fopen(argv[2], "r");

    if (fp1 == NULL || fp2 == NULL) {
        fprintf(stderr, "Error opening files.\n");
        return 1;
    }

    char line1[MAXLINE], line2[MAXLINE];
    int line_number = 0;

    while (fgets(line1, MAXLINE, fp1) && fgets(line2, MAXLINE, fp2)) {
        line_number++;
        if (strcmp(line1, line2) != 0) {
            printf("Files differ at line %d:\n", line_number);
            printf("File1: %sFile2: %s", line1, line2);
            fclose(fp1);
            fclose(fp2);
            return 0;
        }
    }

    // Handle case where one file is longer
    if (fgets(line1, MAXLINE, fp1)) {
        printf("Files differ at line %d:\nFile1 has extra line: %s", ++line_number, line1);
    } else if (fgets(line2, MAXLINE, fp2)) {
        printf("Files differ at line %d:\nFile2 has extra line: %s", ++line_number, line2);
    } else {
        printf("Files are identical.\n");
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
