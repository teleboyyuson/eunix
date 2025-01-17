#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>

int main() {
    // Using standard headers
    printf("Ranges using standard headers:\n");
    printf("char: %d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("int: %d to %d\n", INT_MIN, INT_MAX);
    printf("long: %ld to %ld\n", LONG_MIN, LONG_MAX);

    printf("float: %e to %e\n", FLT_MIN, FLT_MAX);
    printf("double: %e to %e\n", DBL_MIN, DBL_MAX);
    printf("long double: %Le to %Le\n", LDBL_MIN, LDBL_MAX);

    // Direct computation
    printf("\nRanges using direct computation:\n");

    // Char range
    char char_min = 0;
    char char_max = 0;
    while ((char)(char_min - 1) < char_min) char_min--;
    while ((char)(char_max + 1) > char_max) char_max++;
    printf("char: %d to %d\n", char_min, char_max);

    // Short range
    short short_min = 0;
    short short_max = 0;
    while ((short)(short_min - 1) < short_min) short_min--;
    while ((short)(short_max + 1) > short_max) short_max++;
    printf("short: %d to %d\n", short_min, short_max);

    // Int range
    int int_min = 0;
    int int_max = 0;
    while ((int)(int_min - 1) < int_min) int_min--;
    while ((int)(int_max + 1) > int_max) int_max++;
    printf("int: %d to %d\n", int_min, int_max);

    // Long range
    long long_min = 0;
    long long_max = 0;
    while ((long)(long_min - 1) < long_min) long_min--;
    while ((long)(long_max + 1) > long_max) long_max++;
    printf("long: %ld to %ld\n", long_min, long_max);

    // Float range
    float float_min = 1.0;
    float float_max = 1.0;
    while (float_min / 2 > 0) float_min /= 2;
    while (!isinf(float_max * 2)) float_max *= 2;
    printf("float: %e to %e\n", float_min, float_max);

    // Double range
    double double_min = 1.0;
    double double_max = 1.0;
    while (double_min / 2 > 0) double_min /= 2;
    while (!isinf(double_max * 2)) double_max *= 2;
    printf("double: %e to %e\n", double_min, double_max);

    // Long double range
    long double ldouble_min = 1.0;
    long double ldouble_max = 1.0;
    while (ldouble_min / 2 > 0) ldouble_min /= 2;
    while (!isinf(ldouble_max * 2)) ldouble_max *= 2;
    printf("long double: %Le to %Le\n", ldouble_min, ldouble_max);

    return 0;
    exit(0);
}
