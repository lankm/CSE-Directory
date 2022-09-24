#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STRLEN 20

short b10_to_b7(short num) {
    short output=0;

    int base=7;

    for(int power=5; power>=0; power--) {   //divides by powers of 7 until all digits are accounted for. 7^6 is larger than max_short so 7^5 is used.
        int quotient=num/((int)pow(base,power));
        num%=(int)pow(base,power);

        output+=quotient*pow(10,power);
    }

    return output;
}
short b7_to_b10(short num) {
    short output=0;

    int base=7;

    for(int power=5; power>=0; power--) {   
        int digit=(int)(num/(int)pow(10,power)%10); //gets the digit the be used to add.

        output+=digit*pow(base,power);  //gets the value of the digit and adds to output.
    }

    return output;
}

int main() {
    char line[STRLEN];  
    short B10, B7;

    printf("Enter a number in base 10: ");   //getting input
    fgets(line, STRLEN, stdin);
    sscanf(line, "%hi",&B10);  //gets the short value

    B7=b10_to_b7(B10);  //converting
    B10=b7_to_b10(B7);

    printf("Converted to base 7: %hi\n", B7);   //output
    printf("Converted back to base 10: %hi", B10);

    return 0;
}