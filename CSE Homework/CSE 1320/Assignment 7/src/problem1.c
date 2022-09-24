#include "problem1.h"
#include "debug.h"

void showList(char list[][BUF_SIZE] , int size) {  //IO methods.
    for(int i=0; i<size; i++) {
        printf("%d. %s", i+1, list[i]);
    }
}
void print_array(dynamic_array_t *array) {
    for (int i = 0; i < array->size - 1; i++) {
        hash_element_t *elem = array->data[i];
        printf("%s, ", ((vehicle_t *)elem->value)->license_plate);
    }
    hash_element_t *elem = array->data[array->size - 1];
    printf("%s\n", ((vehicle_t *)elem->value)->license_plate);
}

void addVehicle(hash_map_t *map) {  //commands
    printf("Enter a LIC#: ");
    char buffer[BUF_SIZE] = { 0 };
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strlen(buffer) - 1] = 0;

    hash_element_t *elem = search(map, buffer);

    if (elem != NULL) {
        printf("%s is already in the hashmap\n\n", buffer);
        return;
    }

    // Copy the data to a hash_element_t
    elem = calloc(1, sizeof(hash_element_t));
    elem->key = malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(elem->key, buffer);

    // Get value from the user
    vehicle_t *v = calloc(1, sizeof(vehicle_t));

    v->license_plate = calloc(strlen(elem->key) + 1, sizeof(char));
    strcpy(v->license_plate, elem->key);

    input_vehicle(v);

    elem->value = v;

    // Add element to the map
    insert(map, elem);
    printf("Vehicle added.\n\n");
}
void importFile(hash_map_t *map) {
    printf("Enter filename: ");
    char buff[BUF_SIZE];
    fgets(buff, BUF_SIZE, stdin);
    buff[strlen(buff)-1]=0;   //trim

    FILE *fp = fopen(buff, "r");  //opens file and exits if not found.
    if(fp==NULL) {
        printf("\"%s\" could not be found. Returning to home.\n\n", buff);
        return;
    }

    char file_type[BUF_SIZE];
    strcpy(file_type, strchr(buff, '.'));
    if(strcmp(file_type, ".csv")) {  //determines whether the file type is correct.
        printf("Invalid file type. Returning to home.\n\n");
        return;
    }

    load_vehicles(fp, map);
    printf("Import complete.\n\n");
    
}
void vehicleLookup(hash_map_t *map) {
    printf("Enter a LIC#: ");
    char buffer[BUF_SIZE] = { 0 };
    fgets(buffer, BUF_SIZE, stdin);
    buffer[strlen(buffer) - 1] = 0;

    hash_element_t *elem = search(map, buffer);

    if (elem != NULL) {
        printf("%s found!\n", buffer);
        print_vehicle(elem->value);
    } else {
        printf("No vehicle found with that LIC#\n");
    }

    printf("\n");
}
void printMap(dynamic_array_t **list, int array_size) {
    for (int i = 0; i < array_size; i++) {
        printf("map[%d] = ", i);
        if (list[i] == NULL) {
            printf("EMPTY\n");
        } else {
            print_array(list[i]);
        }
    }
    printf("\n");
}
void quit(hash_map_t *map) {
    printf("Exiting program...\n");
}
void error() {
    printf("Wrong input. Returning to home...\n\n");
}

void free_arr(dynamic_array_t **array, int size) {
    if(array==NULL)
        return;

    for(int i=0; i<size; i++) {
        dynamic_array_t *cur = array[i];

        if(cur==NULL)
            continue;

        for (int i = 0; i < cur->size; i++) {
            hash_element_t *elem = cur->data[i];
            vehicle_t *v=((vehicle_t *)elem->value);

            free(v->make);
            free(v->model);
            free(v->color);
            free(v->license_plate);
            free(v);
        }
        free(cur);
    }
}

int main() {
    char commands[][BUF_SIZE] = {"Add Vehicle\n","Import File\n","Vehicle Lookup\n", "Print Map\n", "Quit\n"};
    hash_map_t *map = calloc(1, sizeof(hash_map_t));
    init_map(map, 4);
    

    int status = 1;
    while(status) {
        showList(commands, 5);
        char buff[BUF_SIZE];

        printf("> ");
        fgets(buff, BUF_SIZE, stdin);
        buff[strlen(buff)-1]=0;   //trim
        int input = atoi(buff);
        
        switch (input) {
            case 1: addVehicle(map); break;
            case 2: importFile(map); break;
            case 3: vehicleLookup(map); break;
            case 4: 
                printf("primary list.\n");
                printMap(map->primary, map->map_size);

                printf("temporary list.\n");
                if(map->temp!=NULL) {
                    printMap(map->temp, map->temp_size);
                } else {
                    printf("Empty.\n\n");
                }
                break;
            case 5: quit(map); status = 0; break;

            default: error(); break;
        }
    }

    free_arr(map->primary, map->map_size);
    free_arr(map->temp, map->temp_size);
    free(map);

    printf("Data freed.\n");
    return 1;
}
