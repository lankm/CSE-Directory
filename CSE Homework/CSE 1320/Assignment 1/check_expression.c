#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 20

char OPERATORS[]={'+','-','*','/'}; //I was getting a weird issue when I used #define

int checkExpression(char *str) { //I would use regex normally but google says c doesn't have that built in
    float num1=0;
    char op1=0;
    float num2=0;
    char op2=0;
    float num3=0;
    char extraData[BUFFER_SIZE];

    /*
     *Checks and stores the five variables. checks whether or not there was only 5 inputs
     */
    if(sscanf(str, "%f %c %f %c %f%s", &num1, &op1, &num2, &op2, &num3, &extraData)!=5) 
        return 0;

    if(!strchr(OPERATORS,op1)|!strchr(OPERATORS,op2)) //check whether the two operators are valid.
        return 0;

    return 1;
}

int main() {
    char str[BUFFER_SIZE];

    printf("> ");   //input
    fgets(str, BUFFER_SIZE, stdin);

    if(checkExpression(str))
        printf("Valid expression.");
    else
        printf("Invalid expression.");

    return 1;
}