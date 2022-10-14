/* This header file implements a fixed point uint32_t.
 * The overflow of this number is put into a int64_t.
 * 
 * The purpose of this implemtation is to be take advantage of a couple
 * coincidences: 2^30 ~= 10^9, and cpus are usually 64bit so 32b*32b->64b.
 * 
 * Honestly this should be in assembly.
 * currently implemented with uint32_t having offset 32, not 30(planned).
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
    uint32_t decimal;
    int64_t integer;
} FIX64;

/* parses a string into FIX64 format */
FIX64 convert(char* str)
{
    char* dec_str = strchr(str, '.');
    double dec = atof(dec_str);

    FIX64 fix;
    fix.integer = atoll(str);
    fix.decimal = (uint32_t)(dec*(1<<16)*(1<<16)); //doesnt implement use for first 2 bits
    printf("fix.decimal: %08x\n", fix.decimal);

    return fix;
}
void printFix64(FIX64 num) {
    double dec = ((double)(num.decimal))/(1<<16)/(1<<16);
    printf("%lld %.9lf\n", num.integer, dec);
}

// only works for positive numbers rn
FIX64 add(FIX64 a, FIX64 b)
{
    int64_t val = (int64_t)a.decimal + (int64_t)b.decimal;

    FIX64 fix;
    fix.decimal = (int32_t)val;
    fix.integer = a.integer + b.integer + (val>>32);

    return fix;
}
FIX64 mul(FIX64 a, FIX64 b)
{
    FIX64 fix;//debug this
    int64_t val = (int64_t)a.decimal * (int64_t)b.decimal;
    fix.decimal = (int32_t)(val>>32) + (int64_t)a.decimal*;
    fix.integer = a.integer * b.integer + (val>>63);

    return fix;
}





#endif
