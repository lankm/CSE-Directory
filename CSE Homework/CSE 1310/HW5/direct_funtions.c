//Name: Landon Moon
//ID: 1001906270
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int leapYear(int year) {
    return year%4; //only the last two digits matter but that effeciency problem doesn't matter.
}
int three_nums(int nums[3]) { //would make it work for any size of numbers but im lazy at the moment
    for(int i=0; i<2; i++) { //only goes to 2 because it compared the current to the next 
        if(nums[i]>=nums[i+1])
            return 0;
    }
    return 1;
}
void print_out(int num, char car, char str[]) { //if an even number is given, the message slightly to the lower left then center cause it can't be center
    int length = strlen(str);
    if(num-2<length) { //+2 because of the left and right borders
        printf("Can't print this :(");
        return;
    }

    for(int i=0; i<num; i++) { //top row
        printf("%c",car);
    }
    printf("\n");
    for(int i=0; i<num-2; i++) { //-2 because the first and last rows are already done.
        if(i==((num-2)/2)) { //center message
            int lpadding = (num-length-2)/2; //-2 because of the borders
            int rpadding = num-length-2-lpadding; //just whatever space is left over.
            
            printf("%c",car); //left symbol
            for(int j=0; j<lpadding; j++) //left spaces
                printf(" ");
            printf("%s",str); //message
            for(int j=0; j<rpadding; j++) //right spaces
                printf(" ");
            printf("%c",car); //right symbol
        }
        else //everything else
            for(int j=0; j<num; j++) {
                if(j==0||j==(num-1)) //left and right borders
                    printf("%c",car);
                else
                    printf(" ");
            }
        printf("\n");
    }
    for(int i=0; i<num; i++) { //bottom row
        printf("%c",car);
    }
}
int main(int argc, char **argv) {
    int three_ints[]={3,10,12};

    printf("%d", leapYear(2020));
    printf("%d\n", three_nums(three_ints)); //added \n to make the formatting look better
    print_out(10, '*', "Hello");
}