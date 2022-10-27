/* This header file implements a fixed point uint32_t.
 * The overflow of this number is put into a int64_t.
 * 
 * The purpose of this implemtation is to be take advantage of a couple
 * coincidences: 2^30 ~= 10^9, and cpus are usually 64bit so 32b*32b->64b.
 * 
 * Honestly this should be in assembly.
 *
 * Author: Landon Moon
 * In progress
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifndef FIXED64
#define FIXED64

typedef struct fix64 
{
    int64_t integer;
    uint32_t decimal;
} FIX64;

/* the bits are stored correctly */
FIX64 convert(char* str)
{
    
}
/* works sometimes. focus on bits for now */
void printFix64(FIX64 num) {
    
}

FIX64 add(FIX64 a, FIX64 b)
{
    int64_t val = (int64_t)a.decimal + (int64_t)b.decimal;

    FIX64 num;
    num.decimal = (uint32_t)val;
    num.integer = a.integer + b.integer + (val>>32);

    return num;
}
FIX64 sub(FIX64 a, FIX64 b)
{
    int64_t val = (int64_t)a.decimal - (int64_t)b.decimal;

    FIX64 num;
    num.decimal = (uint32_t)val;
    num.integer = a.integer - b.integer;

    return num;
}
FIX64 mul(FIX64 a, FIX64 b)
{
    FIX64 num;
    int64_t dec = ((int64_t)a.decimal * (int64_t)b.decimal)>>32;
    int64_t cross1 = a.decimal*b.integer;
    int64_t cross2 = b.decimal*a.integer;
    int64_t in = a.integer*b.integer;

    num.decimal = (int32_t)dec + (int32_t)cross1 + (int32_t)cross2;
    num.integer = in + (cross1>>32) + (cross2>>32);

    return num;
}





#endif
