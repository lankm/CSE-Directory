#include <stdio.h>
#include <math.h>

char byte_avg(char c) {

    int total=0;
    int total_num=0;
    for(short i=8; i>0; i--) {

        short upperline=(short)pow(2,i);
        short lowerline=(short)pow(2,i-1);
        unsigned bitVal=(c%upperline)/lowerline; //determines the current bit. Learned unsigned works like a single bit data type.

        if(bitVal==1)
            total_num++;

        total+=bitVal*i;
        //printf("DEBUG:%d %d\n",total, total_num);
    }

    int index=total/total_num;         //needed to round up so a float instead of int. then round the float up and cast to an int.
    return (int)pow(2,index-1);
}
int main() {
    printf("Enter a character: ");
    char c=getchar();

    int total_bits=0;
    printf("> ");
    for(short i=8; i>0; i--) {

        short upperline=(short)pow(2,i);
        short lowerline=(short)pow(2,i-1);
        unsigned bitVal=(c%upperline)/lowerline; //determines the current bit. Learned unsigned works like a single bit data type.

        printf("%d", bitVal);
    }

    printf("\nAverage bit: ");
    char avg=byte_avg(c);
    for(short i=8; i>0; i--) {

        short upperline=(short)pow(2,i);
        short lowerline=(short)pow(2,i-1);
        unsigned bitVal=(avg%upperline)/lowerline; //determines the current bit. Learned unsigned works like a single bit data type.

        printf("%d", bitVal);
    }


}