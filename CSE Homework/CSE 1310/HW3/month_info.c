//Student Name: Landon Moon
//Student ID: 1001906270
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char months[12][20] = {
        "Janurary",
        "Feburary",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
};
const char orders[12][20] = {
        "first",
        "second",
        "third",
        "fourth",
        "fifth",
        "sixth",
        "seventh",
        "eighth",
        "nineth",
        "tenth",
        "eleventh",
        "twelfth"
};

int main(int argc, char **argv) {
    char month[20];
    char matMonth[20]; //the formatted month to compare to the array
    printf("Please enter the name of a month: ");   //gets input
    scanf("%s", month);


    for(int i = 1; month[i]; i++){ //makes every letter lowercase except the first which is uppercase
        matMonth[i] = tolower(month[i]);
    }
    matMonth[0] = toupper(month[0]);

    for(int i = 0; i<12; i++) {    //searching through the array
        if(strcmp(matMonth,months[i])==0) {
            printf("%s is the %s month.",matMonth,orders[i]);
            return 1;   //exit if successful
        }
    }
    printf("Unknown month: %s", month);
}