#include <stdio.h>
#include <math.h>

#define BUFFER_SIZE 20

int main() {
    int num=-1;
    char str[BUFFER_SIZE];

    printf("Enter an integer: ");   //input
    fgets(str, BUFFER_SIZE, stdin);
    sscanf(str, "%d", &num);

    int factors[num];   //generates factors
    int size=0;
    for(int i=1; i<=num;i++) {  //is ineffiecient. Going to the square of num and finding the matching factors is fastest.
        if(num%i==0) {
            factors[size]=i;
            size++;
        }
    }

    if(size==2) //is prime
        printf("%d is prime!\n",num);
    else if(size<=4) {//4 or fewer factors
        for(int i=0;i<size;i++) {
            printf("%9d\n",factors[i]);
        }
    }
    else {  //prints first two and last two
        for (int i = 1; i < 3; i++) {
            printf("%9d\n",factors[i]);
        }
        for (int i = size-3; i < size-1; i++) {
            printf("%9d\n",factors[i]);
        }
    }

    return 0;
}
