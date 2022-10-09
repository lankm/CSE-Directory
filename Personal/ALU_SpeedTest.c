#include <time.h>
#include <stdio.h>
#include <stdint.h>

#define LOOP_NUM 200000000

int main() {
    clock_t start, end;

    int32_t ia=1, ib;
    int64_t la=1, lb;
    float fa=1, fb;
    double da=1, db;


    int i=0;
    start = clock();
    for(;i<LOOP_NUM*3; i++) {}
    end = clock();
    clock_t baseline=(end-start)/3;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {ib+=ia;}
    end = clock();
    clock_t int_add=end-start-baseline;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {ib*=ia;}
    end = clock();
    clock_t int_mul=end-start-baseline;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {lb+=la;}
    end = clock();
    clock_t long_add=end-start-baseline;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {lb*=la;}
    end = clock();
    clock_t long_mul=end-start-baseline;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {fb+=fa;}
    end = clock();
    clock_t float_add=end-start-baseline;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {fb*=fa;}
    end = clock();
    clock_t float_mul=end-start-baseline;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {db+=da;}
    end = clock();
    clock_t double_add=end-start-baseline;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {db*=da;}
    end = clock();
    clock_t double_mul=end-start-baseline;


    
    printf("%8s|%8s|%8s|\n","type","add/sub","mul/div");
    printf("%8s|%8d|%8d|\n","int32",int_add,int_mul);
    printf("%8s|%8d|%8d|\n","int64",long_add,long_mul);
    printf("%8s|%8d|%8d|\n","float",float_add,float_mul);
    printf("%8s|%8d|%8d|\n","double",double_add,double_mul);
}


/* results on personal machine.
    type| add/sub| mul/div|
   int32|       3|      64|
   int64|       5|       3| Winner
   float|      88|      88|
  double|      88|      89|
*/