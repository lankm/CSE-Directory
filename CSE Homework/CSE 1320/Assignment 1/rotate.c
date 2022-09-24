#include <stdio.h>

#define BUFFER_SIZE 20

char rotate(unsigned char c, int move) {
    move%=94; //gets rid of negetives
    move+=94; 
    move%=94;

    c-=33;  //move the character
    c+=move;
    c%=94;
    c+=33;

    return c;
}
int main() {
    char str[BUFFER_SIZE];
    unsigned char c=0; //got some overflow problems so it has to be unsigned.
    int move=0;

    printf("> ");   //input
    fgets(str, BUFFER_SIZE, stdin);
    sscanf(str, "%c %d", &c, &move);

    char newC=rotate(c,move);

    printf("%c", newC);

    return 1;
}
