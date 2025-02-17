#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]) {
    int i = 0, j = 0;
    char c;

    while (s1[i] != '\0') {
        if (s1[i] == '-' && i > 0 && s1[i+1] != '\0' && s1[i-1] < s1[i+1]) {
            for (c = s1[i-1] + 1; c <= s1[i+1]; c++) {
                s2[j++] = c;
            }
            i += 2; // Skip the end character, as it's already included
        } else {
            s2[j++] = s1[i++];
        }
    }
    s2[j] = '\0';
}

int main() {
    char s1[] = "a-d 0-3 A-C";
    char s2[100];

    expand(s1, s2);
    printf("Expanded: %s\n", s2);

    return 0;
}
