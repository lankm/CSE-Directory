#include <stdio.h>
#include "vector_types.h"

void vec_add(float *result, float *a, float *b, short size) {
    //assumes both inputs are the same length
    for(int i=0; i<size; i++) {
        result[i]=a[i]+b[i];
    }
}
void sclr_mult(float *result, float *a, float b, short size) {
    for(int i=0; i<size; i++) {
        result[i]=a[i]*b;
    }
}
void vec_prt(float *a, short size) {
    printf("[");
    for(int i=0; i<size; i++) {
        printf("%.2f", a[i]);
        if(i+1<size)
            printf(", ");
    }
    printf("]");
}
int main() {
    vec2f a1={3,1}, b1={4.3,1}, c1; //vector addition. change numbers for different input
    vec_add(c1, a1, b1, sizeof(a1)/sizeof(*a1));

    vec_prt(a1, sizeof(a1)/sizeof(*a1));  //could probably condense this into a method.
    printf(" + ");
    vec_prt(b1, sizeof(b1)/sizeof(*b1));
    printf(" = ");
    vec_prt(c1, sizeof(c1)/sizeof(*c1));
    printf("\n");



    vec4f a2={4,5,2,7}, c2; //vector multiplication. change numbers for different input
    float b2=3.3;
    sclr_mult(c2, a2, b2, sizeof(a2)/sizeof(*a2));

    printf("%.2f * ", b2);
    vec_prt(a2, sizeof(a2)/sizeof(*a2));
    printf(" = ");
    vec_prt(c2, sizeof(a2)/sizeof(*a2));


    return 0;
}