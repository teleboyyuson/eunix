#include <stdio.h>
#include <stdarg.h>

void minscanf(const char *fmt, ...) {
    va_list ap;
    const char *p;
    int *ival;
    float *fval;
    char *sval;
    char *cval;  // Corrected: Pointer to store character

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            continue;
        }

        p++;  // Move past '%'
        switch (*p) {
            case 'd':  // Integer
                ival = va_arg(ap, int *);
                scanf("%d", ival);
                break;
            case 'f':  // Float
                fval = va_arg(ap, float *);
                scanf("%f", fval);
                break;
            case 's':  // String
                sval = va_arg(ap, char *);
                scanf("%s", sval);
                break;
            case 'c':  // Character (Fixed)
                cval = va_arg(ap, char *);
                scanf(" %c", cval);  // Space before %c prevents newline issues
                break;
            default:
                printf("Unsupported format specifier: %%%c\n", *p);
                break;
        }
    }
    va_end(ap);
}

int main() {
    int num;
    float fnum;
    char str[100];
    char ch;

    printf("Enter an integer: ");
    minscanf("%d", &num);

    printf("Enter a float: ");
    minscanf("%f", &fnum);

    printf("Enter a string: ");
    minscanf("%s", str);

    printf("Enter a character: ");
    minscanf("%c", &ch);

    printf("\nYou entered:\n");
    printf("Integer: %d\n", num);
    printf("Float: %f\n", fnum);
    printf("String: %s\n", str);
    printf("Character: %c\n", ch);

    return 0;
}

