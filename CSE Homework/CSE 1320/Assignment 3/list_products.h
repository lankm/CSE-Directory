#ifndef LIST_PRODUCTS_H_
#define LIST_PRODUCTS_H_

#include <stdio.h>

typedef struct {
    int ID;
    char Name[128];
    double Price;
    int Quantity;
} data;

typedef data (*fnct_ptr)(FILE*);
void print_data(fnct_ptr, FILE*);

data read_CSV_line(FILE *);
data read_BIN_line(FILE *);

#endif