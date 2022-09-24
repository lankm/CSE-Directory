#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debug.h"
#include "utils/hash_map_utils.h"

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

vehicle_t *input_vehicle(vehicle_t *v);
vehicle_t **load_vehicles(FILE *fp, hash_map_t *map);   //idk why you put this in the vehicles file. Size cant come out of the method so im just loading it into the map here.
void print_vehicle(vehicle_t *v);

#endif
