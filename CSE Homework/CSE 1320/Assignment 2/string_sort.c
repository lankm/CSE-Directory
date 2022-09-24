#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IN_NUM 4
#define STRLEN 128

int compare(const void *a, const void *b) { //in same format as qsort for practice. I don't use qsort because thats not the assignment.
    char *str1 = (char*)a;
    char *str2 = (char*)b;

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    return len1-len2;
}

void insertStr(char arr[IN_NUM][STRLEN], char str[STRLEN]) {
    for(int i=0; i<IN_NUM; i++) {
        if(compare(str, arr[i])>0) {    //if the str is larger than the current index.
            for(int j=IN_NUM-1; j>i; j--) {  //moves following indexes forward one. makes room for new str.
                strcpy(arr[j],arr[j-1]);
            }

            strcpy(arr[i],str); //inserts string in correct postition.
            break;
        }
    }
}

int main() {
    char lines[IN_NUM][STRLEN];
    char line[STRLEN];
    int num;

    int i=0;
    for(; i<IN_NUM; i++) {
        printf("Enter a string: ");   //getting strings
        fgets(line, STRLEN, stdin);
        insertStr(lines,line);  //insert the string into the correct position

        if(strcmp(lines[i],"\n")==0) {  //exits if no input
            break;
        }
    }

    printf("%d strings read.\n", i);  //displays num of inputs
    for(int j=0; j<i; j++) {    //prints lines[][]
        printf("%s",lines[j]);  //no \n needed because strings already have them.
    }

    return 0;
}