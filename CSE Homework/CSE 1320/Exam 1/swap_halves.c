#include <stdio.h>
#include <string.h>

#define BUF_SIZE 128

void trim(char *str) {
    int l = strlen(str);
    if (str[l-1] == '\n') {
        str[l-1] = 0;
    }
}

void swap_halves(char *str) {
    int len = strlen(str);
    int mid_point = len / 2;

    char buffer[BUF_SIZE] = { 0 };

    
    strcpy(buffer, str+mid_point);
    strcat(buffer, str);    //buffer becomes longer than original string but because its cut off when copying, behavior is normal.

    for(int i=0; i<len;i++) {   //propperly coppying data.
        str[i]=buffer[i];
    }
}

int main() {
    char input[BUF_SIZE] = { 0 }; //made buffer larger

    printf("Enter a string: ");
    fgets(input, BUF_SIZE, stdin);  //did fgets instead of scanf
    trim(input);

    printf("Before swap: %s\n", input);

    swap_halves(input);

    printf("After swap: %s\n", input);

    return 0;
}
