/* Comment
# This is a Header



This is a comment
and this is another
*/

#include <stdio.h>

int x;
int y;
int z;

x = 10;
y = 11;

int addnumbers(int x, int y);

/*# This is the main function */


int main(){
    x = 5;
    y = 10;
    z = x + y;
    printf("Enter the value of x: ");
    scanf("%d", &x); 
    printf("The value of x in int main: %d \n", x);
    printf("The value of y in int main: %d \n", y);
    printf("z is equals to %d \n", z);
    printf("intaddnumbers z is equals to %d \n", addnumbers(x,y));
    
    return 0;
}


int addnumbers(int x, int y){
    x = 1;
    y = 3;
    z = x + y;
    printf("The value of x in int addnumbers: %d \n", x);
    printf("The value of y in int addnumbers: %d \n", y);
    printf("The value of z in int addnumbers: %d \n", z);
    return z;
    
}

