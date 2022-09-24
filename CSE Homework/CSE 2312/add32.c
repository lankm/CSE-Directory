#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern uint32_t addU32(uint32_t x, uint32_t y);
extern int32_t addS32(int32_t x, int32_t y);

int main(void)
{
    uint32_t a, b, c;
    a = 1000000;
    b = 2000000;
    c = addU32(a, b);
    printf("%u + %u = %u\n", a, b, c);

    int32_t d, e, f;
    d = -1000000;
    e = 2000000;
    f = addS32(d, e);
    printf("%d + %d = %d\n", d, e, f);
}
