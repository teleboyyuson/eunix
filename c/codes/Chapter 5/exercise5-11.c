#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB 8

int get_tabstop(int pos, int argc, char *argv[]) {
    int tabstop;

    if (argc > 1) {
        int i;
        for (i = 1; i < argc; i++) {
            tabstop = atoi(argv[i]);
            if (tabstop > pos) {
                return tabstop - pos;
            }
        }
    }
    return DEFAULT_TAB - (pos % DEFAULT_TAB);
}

int main(int argc, char *argv[]) {
    int c, pos = 0, spaces = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            spaces++;
            if (spaces == get_tabstop(pos, argc, argv)) {
                putchar('\t');
                spaces = 0;
                pos += get_tabstop(pos, argc, argv);
            }
        } else {
            while (spaces > 0) {
                putchar(' ');
                spaces--;
                pos++;
            }
            putchar(c);
            if (c == '\n') {
                pos = 0;
            } else {
                pos++;
            }
        }
    }

    return 0;
}
