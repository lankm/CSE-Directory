#include "fixed64.h"
#include <stdio.h>

int main()
{
    char *max = "-9223372036854775807.9999999996";
    char *val1 = "-3";
    char *val2 = "-7.25";
    FIX64 num1 = convert(val1);
    FIX64 num2 = convert(val2);
    
    char *str = malloc(FIX64_MAX_STR_LENGTH);
    printf("%s\n", toString(str, sub(num1, num2)));

}
