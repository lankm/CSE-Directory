#include "vehicle.h"


/*
 * Reads in vehicle data for a single vehicle form the user.
 * If the input vehicle is NOT NULL, only the NON-NULL entries
 * will be requested from the user.
 */
vehicle_t *input_vehicle(vehicle_t *v) {
    char buffer[BUF_SIZE] = { 0 };

    if (v == NULL) {
        v = calloc(1, sizeof(vehicle_t));
    }

    if (v->year == 0) {
        printf("Enter year: ");
        scanf("%d", &v->year);
        while (getchar() != '\n');
    }

    if (v->make == NULL) {
        printf("Enter make: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        v->make = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(v->make, buffer);
    }

    if (v->model == NULL) {
        printf("Enter model: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        v->model = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(v->model, buffer);
    }

    if (v->color == NULL) {
        printf("Enter color: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        v->color = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(v->color, buffer);
    }

    if (v->license_plate == NULL) {
        printf("Enter license plate: ");
        fgets(buffer, BUF_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;
        v->license_plate = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(v->license_plate, buffer);
    }

    return v;
}

/*
 * Loads vehicles from a file.
 * If `keys` is NOT NULL, this function will not save any vehicle
 * that has a key in `keys`.
 */
vehicle_t **load_vehicles(FILE *fp, hash_map_t *map) {
    vehicle_t **vehicles = NULL;
    int size=0;

    char line[BUF_SIZE];
    fgets(line, BUF_SIZE, fp);

    while(1) {
        
        size++;
        vehicles = realloc(vehicles, size*sizeof(vehicle_t*));
        
        vehicles[size-1] = malloc(sizeof(vehicle_t));


        char buff[BUF_SIZE];
        vehicles[size-1]->year=atoi(strtok(line, ",\n"));

        strcpy(buff, strtok(NULL, ",\n"));
        vehicles[size-1]->make = calloc(strlen(buff), sizeof(char));
        strcpy(vehicles[size-1]->make, buff);

        strcpy(buff, strtok(NULL, ",\n"));
        vehicles[size-1]->model = calloc(strlen(buff), sizeof(char));
        strcpy(vehicles[size-1]->model, buff);

        strcpy(buff, strtok(NULL, ",\n"));
        vehicles[size-1]->color = calloc(strlen(buff), sizeof(char));
        strcpy(vehicles[size-1]->color, buff);

        strcpy(buff, strtok(NULL, ",\n"));
        vehicles[size-1]->license_plate = calloc(strlen(buff), sizeof(char));
        strcpy(vehicles[size-1]->license_plate, buff);

        if(feof(fp))
            break;
        
        fgets(line, BUF_SIZE, fp);
        
    }

    printf("%d Entries to be entered.\n", size);

    while(map->temp!=NULL)  //rehashes everything thats in temp to make room for the extra entries.
        rehash_inc(map);

    double factor = compute_load_factor(map->num_keys+size, map->map_size)/LOAD_FACTOR+1;
    resize_map(map, factor);    //this assumes that there are no duplicates even though i skip duplicates later.

    printf("Rehashing...\n");

    int dup=0;
    for(int i=0;i<size;i++) {
        hash_element_t *elem = calloc(1, sizeof(hash_element_t));
        elem->value = vehicles[i];
        elem->key = vehicles[i]->license_plate;

        hash_element_t *elem2 = search(map, elem->key);

        if (elem2 != NULL) {
            dup++;
            rehash_inc(map);
            continue;
        }

        insert(map, elem);
    }

    printf("%d Duplicates skipped.\n", dup);

    return vehicles;

}

void print_vehicle(vehicle_t *v) {
    printf("%d %s %s (%s) LIC#%s\n", v->year, v->make, v->model, v->color, v->license_plate);
}
