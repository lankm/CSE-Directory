#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int consecBits(FILE *file, short N) {
    unsigned char curByte=fgetc(file);
    int consec=0; //current consecutive bits
    int output=0; //totat times N consecutive bits occur

    while(!feof(file)) {
        printf("DEBUG[%c]: %x  ",curByte ,curByte);   //debug code.
        for(short i=8; i>0; i--) {

            short upperline=(short)pow(2,i);
            short lowerline=(short)pow(2,i-1);
            unsigned bitVal=(curByte%upperline)/lowerline; //determines the current bit. Learned unsigned works like a single bit data type.
            if(bitVal==1) {    
                consec++;
            } else {
                consec=0;
            }
            printf("%x", bitVal); //debug code.

            if(consec>=N)
                output++;
        }
        printf("\n"); //debug code.

        curByte = fgetc(file);
    }

    return output;
}

int main(int argc, const char **argv) {
    if (argc!=3) {
        printf("USAGE: ./a.out FILENAME NUM");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");  //opens file and exits if not found.
    if(file==NULL) {
        printf("\"%s\" could not be found. Exiting program.", argv[1]);
        return 1;
    }

    short N=atoi(argv[2]);
    int csecBits=consecBits(file,N);

    fclose(file);

    printf("%d",csecBits);


    return 0;
}