#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS, QUALIFIER };

int tokentype;
char token[MAXTOKEN];
char out[1000];

int gettoken(void);
void dcl(void);
void dirdcl(void);

int main() {
    while (gettoken() != EOF) {
        strcpy(out, token);
        dcl();
        if (tokentype != '\n') {
            printf("Syntax error\n");
        } else {
            printf("%s\n", out);
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
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        if (strcmp(token, "const") == 0 || strcmp(token, "volatile") == 0) {
            return tokentype = QUALIFIER;
        }
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
    int type;

    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            printf("Error: missing )\n");
        }
    } else if (tokentype == NAME) {
        strcat(out, " ");
        strcat(out, token);
    } else {
        printf("Error: expected name or (dcl)\n");
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == QUALIFIER) {
        if (type == PARENS) {
            strcat(out, " function returning");
        } else if (type == BRACKETS) {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        } else if (type == QUALIFIER) {
            strcat(out, " ");
            strcat(out, token);
        }
    }
}

