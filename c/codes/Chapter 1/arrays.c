#include <stdio.h>
int main()
{
    int c, i, nwhite, nother;
    int ndigit[10];

    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
 printf("digits = ");    
 for (i = 0; i < 10; ++i)
     printf( " %d, other = %d\n",
     nwhite, nother);


return 0;
}
