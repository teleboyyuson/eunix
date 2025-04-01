#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINES 5000 /* max number of lines to be sorted */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort_custom(char *lineptr[], int left, int right, int (*comp)(const char *, const char *));
int strcmp_fold(const char *s1, const char *s2);
int strcmp_normal(const char *s1, const char *s2);

int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int (*compare)(const char *, const char *);

    /* Check for -f option */
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        compare = strcmp_fold;
    } else {
        compare = strcmp_normal;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_custom(lineptr, 0, nlines - 1, compare);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* Read input lines */
int readlines(char *lineptr[], int maxlines) {
    int len, nlines = 0;
    char *p, line[1000];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        len = strlen(line);
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL) {
            return -1;
        }
        line[len - 1] = '\0'; /* Remove newline */
        strcpy(p, line);
        lineptr[nlines++] = p;
    }

    return nlines;
}

/* Write output lines */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

/* Custom quicksort */
void qsort_custom(char *v[], int left, int right, int (*comp)(const char *, const char *)) {
    int i, last;
    void swap(char *v[], int, int);

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort_custom(v, left, last - 1, comp);
    qsort_custom(v, last + 1, right, comp);
}

/* Swap function */
void swap(char *v[], int i, int j) {
    char *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* Normal string comparison */
int strcmp_normal(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}

/* Fold case-insensitive string comparison */
int strcmp_fold(const char *s1, const char *s2) {
    char a, b;

    while (*s1 && *s2) {
        a = tolower((unsigned char)*s1);
        b = tolower((unsigned char)*s2);
        if (a != b) {
            return a - b;
        }
        s1++;
        s2++;
    }

    return (unsigned char)*s1 - (unsigned char)*s2;
}
