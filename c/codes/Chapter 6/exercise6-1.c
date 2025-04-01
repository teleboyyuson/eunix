#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100

int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

int main() {
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        printf("%s\n", word);
    return 0;
}

int getword(char *word, int lim) {
    int c;
    char *w = word;

    while (isspace(c = getch()))  // Skip whitespace
        ;

    if (c != EOF)
        *w++ = c;

    if (c == '_' || isalpha(c)) {  // Handle identifiers (including underscores)
        for (; --lim > 0; w++)
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
    } else if (c == '\"' || c == '\'') {  // Handle string and character constants
        int quote = c;
        while (--lim > 0 && (c = getch()) != quote) {
            if (c == '\\')  // Handle escape sequences
                *w++ = c, c = getch();
            *w++ = c;
            if (c == EOF)
                break;
        }
        *w++ = quote;
    } else if (c == '/') {  // Handle comments
        int next = getch();
        if (next == '/') {  // Single-line comment
            while ((c = getch()) != '\n' && c != EOF)
                ;
        } else if (next == '*') {  // Multi-line comment
            while ((c = getch()) != EOF) {
                if (c == '*' && (c = getch()) == '/')
                    break;
            }
        } else {
            ungetch(next);
        }
    } else if (c == '#') {  // Handle preprocessor lines
        while (--lim > 0 && (c = getch()) != '\n' && c != EOF)
            *w++ = c;
    }

    *w = '\0';
    return c;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
