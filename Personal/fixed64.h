/* This header file implements a fixed point uint32_t.
 * The overflow of this number is put into a int64_t.
 * 
 * The purpose of this implemtation is to be take advantage of a couple
 * coincidences: 2^30 ~= 10^9, and cpus are usually 64bit so 32b*32b->64b.
 * 
 * Honestly this should be in assembly.
 *

    //*(uint64_t*)(&num.f) = 0x888880000000llu; purposly leaking into num.i
 * Author: Landon Moon
 * In progress
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef FIXED64
#define FIXED64

#define FIX64_MAX_STR_LENGTH 31

typedef struct __attribute__((packed)) fix64 
{
    // f then i because x86 is little-endian

    uint32_t : 32; // 4 unused bytes
    uint32_t f; // used as pointer to beginning of bits
    int64_t i;  // used as pointer to integer section
} FIX64;

FIX64 negate(FIX64 *num)
{
    // negative handling
    num->i = ~num->i;
    num->f = ~num->f+1;
    // if overflow
    if(!num->f)
    {
        num->i++;
    }

    return *num;
}

/* Converts a string to FIX64 */
FIX64 convert(char *str)
{   
    // declaring return variable
    FIX64 num;

    // retrieving decimal bits
    char* point = strchr(str, '.');
    double dec = atof(point);
    num.f = (uint32_t)(dec*(1<<16)*(1<<16));

    // if negative
    if(str[0] == '-')
    {
        // retrieving integer bits. skip '-'
        num.i = atoll(++str);

        // negative handling
        negate(&num);
    }
    else
    {
        // retrieving integer bits
        num.i = atoll(str);
    }

    printf("f: %p i: %p\n", &num.f, &num.i);     // print address values
    printf("num: %016llx.%08x\n", num.i, num.f); // print bit values
    
    return num;
}
/* Prints a FIX64. Change to not print and return string */
char* toString(char *str, FIX64 num)
{
    // copying
    FIX64 copy = num;

    // if negative
    if(copy.i < 0)
    {
        // negative handling
        negate(&copy);
        printf("-");
    }

    // edge handling
    if(copy.f >= UINT32_MAX-1)
    {
        copy.f = UINT32_MAX-2;
    }
    // retrieving decimal value
    double dec = ((double)(copy.f))/(1<<16)/(1<<16);
    
    // string handling
    char strBuff[11];
    sprintf(strBuff, "%.9lf", dec);
    sprintf(str, "%lld%s\n", copy.i, strBuff+1);

    return str;
}

FIX64 add(FIX64 a, FIX64 b)
{
    
}
FIX64 sub(FIX64 a, FIX64 b)
{
    
}
FIX64 mul(FIX64 a, FIX64 b)
{
    
}





#endif
