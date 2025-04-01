#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000 /* Maximum number of lines to sort */
#define MAXLEN 1000   /* Maximum length of each line */

char *lineptr[MAXLINES]; /* Pointers to lines */

int read_lines(char *lineptr[], int maxlines);
void write_lines(char *lineptr[], int nlines);
void quick_sort(void *lineptr[], int left, int right,
                 int (*comp)(const void *, const void *, int, int), int fold, int dir);
int custom_strcmp(const char *s1, const char *s2, int fold, int dir);
int is_directory_char(int c);

int main(int argc, char *argv[]) {
    int nlines;       /* Number of lines read */
    int fold = 0;     /* Fold case flag */
    int dir = 0;      /* Directory order flag */

    /* Parse command-line arguments */
    while (--argc > 0 && (*++argv)[0] == '-') {
        switch ((*argv)[1]) {
            case 'f':
                fold = 1;
                break;
            case 'd':
                dir = 1;
                break;
            default:
                fprintf(stderr, "Invalid option: %s\n", *argv);
                return 1;
        }
    }

    /* Read lines */
    if ((nlines = read_lines(lineptr, MAXLINES)) >= 0) {
        /* Sort lines */
        quick_sort((void **) lineptr, 0, nlines - 1,
                   (int (*)(const void *, const void *, int, int)) custom_strcmp, fold, dir);
        /* Output sorted lines */
        write_lines(lineptr, nlines);
        return 0;
    } else {
        fprintf(stderr, "Input too large to sort\n");
        return 1;
    }
}

void quick_sort(void *v[], int left, int right,
                 int (*comp)(const void *, const void *, int, int), int fold, int dir) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) return;

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
        if (comp(v[i], v[left], fold, dir) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    quick_sort(v, left, last - 1, comp, fold, dir);
    quick_sort(v, last + 1, right, comp, fold, dir);
}

int custom_strcmp(const char *s1, const char *s2, int fold, int dir) {
    char a, b;

    do {
        if (dir) {
            while (*s1 && !is_directory_char(*s1)) s1++;
            while (*s2 && !is_directory_char(*s2)) s2++;
        }

        a = (fold && isalpha(*s1)) ? tolower(*s1) : *s1;
        b = (fold && isalpha(*s2)) ? tolower(*s2) : *s2;

        if (a == b && a == '\0')
            return 0;

        s1++;
        s2++;

    } while (a == b);

    return a - b;
}

int is_directory_char(int c) {
    return isalnum(c) || c == ' ';
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int read_lines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char line[MAXLEN], *p;

    while (fgets(line, MAXLEN, stdin) != NULL) {
        len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';

        p = malloc(len + 1);
        if (p == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            return -1;
        }

        strcpy(p, line);
        lineptr[nlines++] = p;

        if (nlines >= maxlines)
            return -1;
    }

    return nlines;
}

void write_lines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}
