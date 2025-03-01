#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* atof: convert string s to double, handling scientific notation */
double atof(const char s[]) {
    double val, power;
    int i, sign, exp_sign, exponent;
    
    for (i = 0; isspace(s[i]); i++)  // Skip whitespace
        ;
    
    sign = (s[i] == '-') ? -1 : 1;  // Handle sign
    if (s[i] == '+' || s[i] == '-')
        i++;
    
    for (val = 0.0; isdigit(s[i]); i++)  // Integer part
        val = 10.0 * val + (s[i] - '0');
    
    if (s[i] == '.')  // Fractional part
        i++;
    
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    val = sign * val / power;
    
    if (s[i] == 'e' || s[i] == 'E') {  // Scientific notation
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        
        for (exponent = 0; isdigit(s[i]); i++)
            exponent = 10 * exponent + (s[i] - '0');
        
        val *= pow(10, exp_sign * exponent);
    }
    
    return val;
}

int main() {
    char s1[] = "123.45e-6";
    char s2[] = "-5.67E3";
    char s3[] = "42";
    char s4[] = "3.14159";
    
    printf("%s = %g\n", s1, atof(s1));
    printf("%s = %g\n", s2, atof(s2));
    printf("%s = %g\n", s3, atof(s3));
    printf("%s = %g\n", s4, atof(s4));
    
    return 0;
}