#include <stdio.h>

#define STRLEN 20


void swap_pointers(int *a, int *b) {
    int temp=*a;
    *a=*b;
    *b=temp;
}


int main() {
    char line[STRLEN];  
    int num1, num2;

    printf("> ");   //getting input
    fgets(line, STRLEN, stdin);
    sscanf(line, "%d %d",&num1, &num2);


    printf("%d %d\n", num1, num2);  //print values of num1 and num2
    swap_pointers(&num1, &num2);    //swap values.
    printf("%d %d\n", num1, num2);  //print values of num1 and num2

    return 0;
}