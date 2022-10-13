/* This header file implements a dynamic array
 *
 * Author: Landon Moon
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef DA
#define DA

typedef struct array
{
    void* arr;

    int size;
    int data_size;
} ARRAY;

/* increases the size of arr*/
void* resize(ARRAY a, int factor)
{
    a.size *= factor;
    a.arr = realloc(a.arr, a.size);
}
void freeArray(ARRAY a)
{
    // arr, ahoy mateys
    free(a.arr);
}

/* basic array functions */



#endif
