#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

void minprintf(const char *fmt, ...) {
    va_list ap;
    const char *p;
    char *sval;
    int ival;
    double dval;
    int width, precision;
    char format[20];

    va_start(ap, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }

        p++;  // Move past '%'
        width = 0;
        precision = -1;

        // Parse width
        if (isdigit(*p)) {
            width = 0;
            while (isdigit(*p)) {
                width = width * 10 + (*p - '0');
                p++;
            }
        }

        // Parse precision
        if (*p == '.') {
            p++;
            precision = 0;
            while (isdigit(*p)) {
                precision = precision * 10 + (*p - '0');
                p++;
            }
        }

        // Format specifier
        switch (*p) {
            case 'd':
            case 'i':
                ival = va_arg(ap, int);
                printf("%*.*d", width, (precision >= 0 ? precision : 1), ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%*.*f", width, (precision >= 0 ? precision : 6), dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                printf("%*.*s", width, (precision >= 0 ? precision : (int)strlen(sval)), sval);
                break;
            case 'c':
                ival = va_arg(ap, int);
                putchar(ival);
                break;
            case '%':
                putchar('%');
                break;
            default:
                putchar('%');
                putchar(*p);
                break;
        }
    }
    va_end(ap);
}

int main() {
    minprintf("Integer: %5d\n", 42);
    minprintf("Float: %10.2f\n", 3.14159);
    minprintf("String: %10.5s\n", "Hello, World!");
    minprintf("Char: %c\n", 'A');
    minprintf("Percent: %%\n");

    return 0;
}
