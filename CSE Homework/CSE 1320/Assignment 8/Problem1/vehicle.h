#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 64
#endif

typedef struct {
    int year;
    char *make;
    char *model;
    char *color;
    char *license_plate;
} vehicle_t;

void print_vehicle(vehicle_t *v);

#endif
