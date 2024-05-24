#include <stdio.h>

int x;
int y;
int z;

int subnumbers(int x, int y);

/*# This is the main function*/

int main (){
    printf("\033[0;32m");
    printf("This is a subtraction program written in C language \n\n\n");
    printf("\033[0m");
    printf("Enter the value of x: ");
    scanf("%d" , &x);
    printf("Enter the value of y: ");
    scanf("%d" , &y);

    printf("The value of z is equals to %d \n\n", subnumbers(x,y));
    printf("Thank you.\n\n");
    return 0;
}


int subnumbers(int x, int y){
   z = x-y;
   return z;
}
