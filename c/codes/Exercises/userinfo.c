#include <stdio.h>

int main(){

    //Title//
    printf("User's Info\n");

    // First Input of User // 
    char name[10]; // 1st variable
    printf("Enter your Name: ");
    scanf("%s", &name);


    //Second Input of User//
    int age; //2nd variable
    printf("Enter your Age: ");
    scanf("%d", &age); 

    getchar();

    //Final Output//
    printf("So your name is %s.You are %d years old\n\n", name, age );

return 0;
}