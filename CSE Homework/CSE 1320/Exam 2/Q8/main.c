#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 128

typedef struct {
    int year;
    char *make;
    char *model;
    char *color;
    char *lic;
} vehicle_t;

typedef struct {
    int num;
    int size;
    vehicle_t **vehicles;
} dynamic_arr;

dynamic_arr* read_data(FILE *fp) {

    dynamic_arr *vehicles = malloc(sizeof(dynamic_arr));
    vehicles->num=0;
    vehicles->size=5;
    vehicles->vehicles = calloc(vehicles->size, sizeof(vehicle_t*));

    for(int i=0;!feof(fp);i++) {
        char line[BUF_SIZE];
        fgets(line, BUF_SIZE, fp);

        char *token = strtok(line, ",");
        int num_tokens = 0;

        vehicle_t* v = malloc(sizeof(vehicle_t));

        while (token != NULL) {     //I really liked how you used a switch and a while statement in the given code for Q7.
            switch (num_tokens) {
                case 0:
                    v->year = atoi(token);
                    break;
                case 1:
                    v->make = calloc(strlen(token), sizeof(char));
                    strcpy(v->make, token);
                    break;
                case 2:
                    v->model = calloc(strlen(token), sizeof(char));
                    strcpy(v->model, token);
                    break;
                case 3:
                    v->color = calloc(strlen(token), sizeof(char));
                    strcpy(v->color, token);
                    break;
                case 4:
                    v->lic = calloc(strlen(token), sizeof(char));
                    strcpy(v->lic, token);
                    break;
            }

            num_tokens++;
            token = strtok(NULL, ",");
        }

        if(i+1 > vehicles->size) {
            vehicles->size*=2;
            vehicles->vehicles = realloc(vehicles->vehicles, vehicles->size * sizeof(vehicle_t*));
        }

        vehicles->vehicles[i] = v;
        vehicles->num++;

    }
    return vehicles;
}

void print_arr(vehicle_t **arr, int size) {
    for(int i=0; i<size; i++) {
        vehicle_t *v = arr[i];

        printf("%d %s %s (%s) LIC#%s", v->year, v->make, v->model, v->color, v->lic);
    }
}

int cmpfunc (const void *a, const void *b) {
    vehicle_t *va = *(vehicle_t**) a;
    vehicle_t *vb = *(vehicle_t**) b;

    return ( va->year - vb->year );
}

int main(int argc, const char **argv) {
    if (argc!=2) {
        printf("USAGE: ./a.out FILENAME");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");  //opens file and exits if not found.
    if(fp==NULL) {
        printf("\"%s\" could not be found. Exiting program.", argv[1]);
        return 1;
    }
    char file_type[BUF_SIZE];
    strcpy(file_type, strchr(argv[1], '.'));
    if(strcmp(file_type, ".csv")) {  //determines whether the file type is correct.
        printf("Invalid file type. Exiting program.");
        return 0;
    }

    dynamic_arr *vehicles = read_data(fp);

    vehicle_t **arr= vehicles->vehicles;

    qsort(arr, vehicles->num, sizeof(vehicle_t*), cmpfunc);

    print_arr(arr, vehicles->num);
    fclose(fp);
}