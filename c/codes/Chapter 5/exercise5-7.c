#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* max #lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */

char *lineptr[MAXLINES]; /* pointers to text lines */
char lines[MAXLINES][MAXLEN]; /* array to hold the lines */

int readlines(char *lineptr[], char lines[][MAXLEN], int maxlines);
void writelines(char *lineptr[], int nlines);
int my_getline(char *s, int lim);

/* Sort input lines */
int main() {
    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, lines, MAXLINES)) >= 0) {
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char *lineptr[], char lines[][MAXLEN], int maxlines) {
    int len, nlines;
    char *p;

    nlines = 0;
    while ((len = my_getline(lines[nlines], MAXLEN)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            lines[nlines][len - 1] = '\0'; /* remove newline */
            lineptr[nlines] = lines[nlines];
            nlines++;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

/* my_getline: read a line into s, return length */
int my_getline(char *s, int lim) {
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }
    if (c == '\n') {
        *s++ = c;
    }
    *s = '\0';
    return s - start;
}
