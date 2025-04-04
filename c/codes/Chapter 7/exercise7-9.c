#include <stdio.h>

#define CHARSET_SIZE 256

// Space-efficient version
int isupper_space(int c) {
    return c >= 'A' && c <= 'Z';
}

// Time-efficient version
char isupper_table[CHARSET_SIZE] = {0};

void init_isupper_table() {
    for (int i = 'A'; i <= 'Z'; ++i)
        isupper_table[i] = 1;
}

int isupper_time(int c) {
    if (c < 0 || c >= CHARSET_SIZE)
        return 0;
    return isupper_table[c];
}

int main() {
    char test[] = {'A', 'a', 'Z', 'z', 'G', '1', '*'};
    int n = sizeof(test) / sizeof(test[0]);

    init_isupper_table();

    printf("Char | isupper_space | isupper_time\n");
    printf("------------------------------------\n");
    for (int i = 0; i < n; i++) {
        char c = test[i];
        printf("  %c   |      %d        |      %d\n", c,
               isupper_space(c), isupper_time(c));
    }

    return 0;
}
