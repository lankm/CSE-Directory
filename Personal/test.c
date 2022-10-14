#include "ll.h"
#include "da.h"
#include "fixed64.h"
#include <stdio.h>

int main()
{
    printf("size: %d\n", sizeof(FIX64));

    char *str1 = "-1.25", *str2 = "1.00000001";
    FIX64 num1 = convert(str1), num2 = convert(str2);
    printFix64(num1);
    printFix64(num2);

    printFix64(mul(num1, num2));
}
