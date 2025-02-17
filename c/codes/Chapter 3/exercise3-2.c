#include <stdio.h>

void escape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
                break;
        }
        i++;
    }
    s[j] = '\0';
}

void unescape(char s[], char t[]) {
    int i = 0, j = 0;
    while (t[i] != '\0') {
        if (t[i] == '\\' && t[i + 1] != '\0') {
            switch (t[i + 1]) {
                case 'n':
                    s[j++] = '\n';
                    i++;
                    break;
                case 't':
                    s[j++] = '\t';
                    i++;
                    break;
                default:
                    s[j++] = t[i];
                    break;
            }
        } else {
            s[j++] = t[i];
        }
        i++;
    }
    s[j] = '\0';
}

int main() {
    char t[] = "Hello\tEunix\nYou're back!";
    char s[100];
    char u[100];

    // Convert to visible escape sequences
    escape(s, t);
    printf("Escaped: %s\n", s);

    // Convert back to original characters
    unescape(u, s);
    printf("Unescaped:\n%s\n", u);

    return 0;
}
