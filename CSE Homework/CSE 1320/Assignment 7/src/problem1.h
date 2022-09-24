#include "utils/hash_map_utils.h"
#include "utils/dynamic_arrays.h"
#include "vehicle.h"


#ifndef PROBLEM_1_
#define PROBLEM_1_

void print_array(dynamic_array_t *);
void showList(char[][BUF_SIZE], int);

void addVehicle(hash_map_t*);  //commands
void importFile(hash_map_t*);
void vehicleLookup(hash_map_t*);
void printMap(dynamic_array_t**, int);
void quit();
void error();

void free_arr(dynamic_array_t **, int);

#endif
