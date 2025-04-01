#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines, int reverse);
void qsort_custom(void *lineptr[], int left, int right,
                  int (*comp)(void *, void *), int reverse);
int numcmp(const char *, const char *);

int main(int argc, char *argv[]) {
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    int reverse = 0; /* 1 if reverse sort */

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (*++argv[0]) {
            switch (*argv[0]) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            default:
                printf("sort: illegal option %c\n", *argv[0]);
                return 1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort_custom((void **) lineptr, 0, nlines - 1,
                     (int (*)(void *, void *))(numeric ? numcmp : strcmp),
                     reverse);
        writelines(lineptr, nlines, reverse);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

#define MAXLEN 1000 /* max length of any input line */
int getline_custom(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = getline_custom(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        line[len - 1] = '\0'; /* remove newline */
        strcpy(p, line);
        lineptr[nlines++] = p;
    }
    return nlines;
}

void writelines(char *lineptr[], int nlines, int reverse) {
    int i;
    if (reverse) {
        for (i = nlines - 1; i >= 0; i--)
            printf("%s\n", lineptr[i]);
    } else {
        for (i = 0; i < nlines; i++)
            printf("%s\n", lineptr[i]);
    }
}

void qsort_custom(void *v[], int left, int right,
                  int (*comp)(void *, void *), int reverse) {
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        if (reverse) {
            if ((*comp)(v[i], v[left]) > 0)
                swap(v, ++last, i);
        } else {
            if ((*comp)(v[i], v[left]) < 0)
                swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort_custom(v, left, last - 1, comp, reverse);
    qsort_custom(v, last + 1, right, comp, reverse);
}

int numcmp(const char *s1, const char *s2) {
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

void swap(void *v[], int i, int j) {
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int getline_custom(char *s, int lim) {
    int c;
    char *p = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *p++ = c;
    if (c == '\n')
        *p++ = c;
    *p = '\0';
    return p - s;
}

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else {
        return NULL;
    }
}
