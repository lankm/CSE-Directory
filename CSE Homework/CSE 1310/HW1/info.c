#include <stdio.h>

int main(int argc, char** argv) {
    char name[20];
    int age;
    char food[20];

    printf("Enter your name:");
    scanf("%s",name);
    
    printf("Enter your age:");
    scanf("%d",&age);

    printf("Enter your favorite candy:");
    scanf("%s",food);

    printf("My name is: %s and my favorite food is %s!\n", name, food);
    printf("***\n");
    printf("I am %d years old and in 2 years i will be %d!", age, age+2);
}