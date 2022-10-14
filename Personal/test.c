#include "fixed64.h"
#include <stdio.h>

int main()
{
    char *max = "-9223372036854775807.9999999996";
    char *val = "-2014242342423424000.1312333755";
    FIX64 num1 = convert(val);
    
    char *str = malloc(FIX64_MAX_STR_LENGTH);
    printf("%s", toString(str, num1));

}
