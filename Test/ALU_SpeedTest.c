#include <time.h>
#include <stdio.h>
#include <stdint.h>

#define LOOP_NUM 100000000

int main() {
    clock_t start, end;

    int32_t ia=1, ic;
    int64_t la=1, lc;
    float fa=1, fc;
    double da=1, dc;


    int i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {}
    end = clock();
    clock_t baseline=end-start;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {ic+=ia;}
    end = clock();
    clock_t int_add=end-start;

    i=0, ic=6;
    start = clock();
    for(;i<LOOP_NUM; i++) {ic*=ia;}
    end = clock();
    clock_t int_mul=end-start;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {lc+=la;}
    end = clock();
    clock_t long_add=end-start;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {lc*=la;}
    end = clock();
    clock_t long_mul=end-start;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {fc+=fa;}
    end = clock();
    clock_t float_add=end-start;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {fc*=fa;}
    end = clock();
    clock_t float_mul=end-start;


    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {dc+=da;}
    end = clock();
    clock_t double_add=end-start;

    i=0;
    start = clock();
    for(;i<LOOP_NUM; i++) {dc*=da;}
    end = clock();
    clock_t double_mul=end-start;


    
    printf("%8s|%8s|%8s|\n","type","add/sub","mul/div");
    printf("%8s|%8d|%8d|\n","int32",int_add,int_mul);
    printf("%8s|%8d|%8d|\n","int64",long_add,long_mul);
    printf("%8s|%8d|%8d|\n","float",float_add,float_mul);
    printf("%8s|%8d|%8d|\n","double",double_add,double_mul);
}
