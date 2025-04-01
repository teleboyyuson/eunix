#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int gettoken(void);
void dcl(void);
void dirdcl(void);

int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type */
char out[1000];          /* output string */

int main() {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n') {
            printf("Syntax error\n");
            while (gettoken() != '\n' && tokentype != EOF)
                ; /* Skip to the next line */
        } else {
            printf("%s: %s %s\n", name, out, datatype);
        }
    }
    return 0;
}

int gettoken(void) {
    int c;
    char *p = token;

    while ((c = getchar()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getchar()) != ']'; )
            if (*(p - 1) == '\n')
                return tokentype = EOF;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

void dcl(void) {
    int ns;
    for (ns = 0; gettoken() == '*'; )
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

void dirdcl(void) {
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')')
            printf("Error: missing )\n");
    } else if (tokentype == NAME) {
        strcpy(name, token);
    } else {
        printf("Error: expected name or (dcl)\n");
    }

    while (gettoken() == PARENS || tokentype == BRACKETS)
        strcat(out, token);
}
