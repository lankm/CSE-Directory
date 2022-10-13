/* This header file implements a fixed point int32_t with a offset of 20 bits.
 * The overflow of this number is put into a int64_t.
 * This results in a min value of a ~10^-6 and a max value of ~10^22.
 * 
 * The purpose of this implemtation is to be as fast as possible while being
 * able to store any astronomical distance uniformly down to the micrometer.
 * The offset is defined as 20; storing that offset in each struct would take
 * up more memory and be slower.
 * 
 * division is excluded due its abysmal performance.
 *
 * Author: Landon Moon
 * In progress
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#ifndef METRIC20
#define METRIC20

#define OFFSET 20

typedef struct mtr20 
{
    int32_t primary;
    int64_t overflow;
} MTR20;

MTR20 add(MTR20 a, MTR20 b)
{

}
MTR20 sub(MTR20 a, MTR20 b)
{

}
MTR20 mul(MTR20 a, MTR20 b)
{

}









#endif
