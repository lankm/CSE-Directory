#include "ll.h"
#include "da.h"
#include <stdio.h>

int main()
{
    ARRAY test;
    test.arr = malloc(sizeof(int)*6);
    test.size = 6;
    test.data_size = sizeof(int);

    ((int*)test.arr)[0] = 2;

    printf("%d", test.size);
}
