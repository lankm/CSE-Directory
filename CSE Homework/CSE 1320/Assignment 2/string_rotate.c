#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IN_NUM 4
#define STRLEN 128

void shift(char arr[IN_NUM+1][STRLEN], int len) { //shifts by 1 index for all in arr[][]
    for(int i=len; i>0; i--) {  //moves all indexes forward one.
        strcpy(arr[i],arr[i-1]);
    }

    strcpy(arr[0], arr[len]);   //moves extranious index to the beginning
}

void rotate(char arr[IN_NUM+1][STRLEN], int num, int len) {   //shifts the array num amount
    for(int i=0; i<num; i++) {
        shift(arr,len);
    }
}

int main() {
    char lines[IN_NUM+1][STRLEN];   //index 0-IN_NUM are used normally. IN_NUM+1 is a temp variable to replace the first.
    char line[STRLEN];
    int num;

    int i=0;
    for(; i<IN_NUM; i++) {
        printf("Enter a string: ");   //getting strings
        fgets(lines[i], STRLEN, stdin);

        if(strcmp(lines[i],"\n")==0) {  //exits if no input
            break;
        }
    }
    printf("%d strings read.\n", i);  //displays num of inputs


    printf("Enter a number: ");   //getting number
    fgets(line, STRLEN, stdin);
    sscanf(line, "%d", &num);

    rotate(lines, num, i);  //rotate by num

    for(int j=0; j<i; j++) {    //prints lines[][]
        printf("%s",lines[j]);
    }

    return 0;
}