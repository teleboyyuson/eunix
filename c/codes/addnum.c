#include <stdio.h>

int x;
int y;
int z;

int addnumbers(int x, int y);

/*# This is the main function */


int main(){
    printf("\033[0;31m");
    printf("This is an addition program written in C language \n\n\n");
    printf("\033[0m");
    printf("Enter the value of x: ");
    scanf("%d", &x); 
    printf("Enter the value of y: ");
    scanf("%d", &y);

    printf("The value of z is equals to %d \n\n", addnumbers(x,y));
    printf("Thank you.\n\n");
    return 0;
}


int addnumbers(int x, int y){
    z = x + y;
    return z;
}

