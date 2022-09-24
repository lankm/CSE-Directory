//Name: Landon Moon
//ID: 1001906270
#include <stdio.h>
#include <string.h> 
#include <ctype.h>
#include <stdlib.h>

int get_input(char message[]) {
    int size = strlen(message)-1;
    for(int i; i<size; i++) { //if its not a number, return INT_MIN
        if(!isdigit(message[i]))
            return INT_MIN;
    }

    return atoi(message); //atoi returns 0 if its not a number.
}
int check_even(int n) {
    if(n%2==0)
        return 1;
    else
        return 0;
}

int main(int argc, char **argv) {
    printf("--Enter an even number:\n");
    while(1) { //even
        char message[20];
        fgets(message, 20, stdin);
        

        int num = get_input(message);

        if(num==INT_MIN){}
        else if(check_even(num)) {
            printf("\n--Ok thanks! Now enter an odd number:\n");
            break;
        }
        printf("that is not even. Enter an even number.\n");
    }

    while(1) { //odd
        char message[20];
        fgets(message, 20, stdin);
        

        int num = get_input(message);

        if(num==INT_MIN){}
        else if(!check_even(num)) {
            printf("\n**Thanks Bye!**\n");
            break;
        }
        printf("that is not odd. Enter an odd number.\n");
    }
}