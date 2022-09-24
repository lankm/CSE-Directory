#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

extern uint64_t addU64(uint64_t x, uint64_t y);

int main(void)
{
    uint64_t a, b, c;
    a = 10000000000;
    b = 20000000000;
    c = addU64(a, b);
    printf("%llu + %llu = %llu\n", a, b, c);
}
