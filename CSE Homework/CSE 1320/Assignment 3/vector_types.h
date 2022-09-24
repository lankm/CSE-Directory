#ifndef VECTOR_TYPES_H_
#define VECTOR_TYPES_H_

typedef float vec2f[2];
typedef float vec3f[3];
typedef float vec4f[4];

void vec_add(float *result, float *a, float *b, short size);
void sclr_mult(float *result, float *a, float b, short size);
void vec_prt(float *a, short size);

#endif
