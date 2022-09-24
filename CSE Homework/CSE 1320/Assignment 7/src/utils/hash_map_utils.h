#ifndef HASH_MAP_UTILS_H_
#define HASH_MAP_UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "dynamic_arrays.h"
#include "../debug.h"

#define LOAD_FACTOR 0.25
#define DEFAULT_RESIZE_FACTOR 2

#define R_VAL(f) (int) ceil(1.0 / ((f) - 1))

typedef struct {
    char *key;
    void *value;
} hash_element_t;

typedef struct {
    dynamic_array_t **temp;
    dynamic_array_t **primary;
    int num_keys;
    int temp_size;
    int map_size;
    int temp_index;
    int r_value;
} hash_map_t;

int hash_function(char *);
int compute_index(char *, int);
double compute_load_factor(int, int);
int matches_key(const void *, char *);
void init_map(hash_map_t *, int);
void resize_map(hash_map_t *, double);
hash_element_t *search(hash_map_t *, char *);
void rehash_inc(hash_map_t *);
void insert_item(dynamic_array_t **, hash_element_t *);
void insert(hash_map_t *, hash_element_t *);

#endif
