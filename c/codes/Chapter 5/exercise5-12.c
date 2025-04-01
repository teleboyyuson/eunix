#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_TAB 8

int get_tabstop(int pos, int start, int step);

int main(int argc, char *argv[]) {
    int c, pos = 1, spaces = 0;
    int start = 0, step = DEFAULT_TAB;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            start = atoi(&argv[i][1]);
        } else if (argv[i][0] == '+') {
            step = atoi(&argv[i][1]);
        }
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            spaces++;
            if (get_tabstop(pos, start, step) == pos) {
                putchar('\t');
                spaces = 0;
            }
        } else {
            while (spaces > 0) {
                putchar(' ');
                spaces--;
            }
            putchar(c);
            if (c == '\n') {
                pos = 1;
            } else {
                pos++;
            }
        }
    }

    return 0;
}

int get_tabstop(int pos, int start, int step) {
    if (pos < start) {
        return DEFAULT_TAB - (pos % DEFAULT_TAB) + pos;
    }
    return ((pos - start) / step + 1) * step + start;
}
