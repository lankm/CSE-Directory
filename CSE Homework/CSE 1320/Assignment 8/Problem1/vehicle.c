#include "vehicle.h"

void print_vehicle(vehicle_t *v) {
    printf("%d %s %s (%s) LIC#%s\n", v->year, v->make, v->model, v->color, v->license_plate);
}
