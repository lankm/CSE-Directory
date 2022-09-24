#ifndef PARKING_REGISTRATION_H_
#define PARKING_REGISTRATION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUF_SIZE 256
#define MAX_STR 64
#define LICENSE_LEN 8

typedef struct {
    int year;
    char make[MAX_STR];
    char model[MAX_STR];
    char color[MAX_STR];
    char license[LICENSE_LEN];
} vehicle_t;

void trim(char *);
FILE *open_database(char *);
vehicle_t parse_vehicle_csv(char *);
void print_vehicle(vehicle_t);
int register_vehicle(FILE *);
void write_data(vehicle_t, FILE *);

#endif
