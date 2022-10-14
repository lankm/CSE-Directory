#include "ll.h"
#include "da.h"
#include "fixed64.h"
#include <stdio.h>

int main()
{
    char* str = "1.5";
    FIX64 numf = convert(str);
    double numd = atof(str);

    printFix64(numf);
    numf = mul(numf, numf);
    printFix64(numf);
    
    printf("%.15lf\n", numd);
}
