#include "problem1.h"

int search_entry(vehicle *entry, const char *str) {
    char str_buffer[STR_BUFF];
    sprintf(str_buffer, "%d", entry->year);
    if(!strcmp(str_buffer, str))
        return 1;

    else if(!strcmp_insensitive(entry->make, str))
        return 1;
    else if(!strcmp_insensitive(entry->model, str))
        return 1;
    else if(!strcmp_insensitive(entry->color, str))
        return 1;
    else if(!strcmp_insensitive(entry->license_plate, str))
        return 1;
    else
        return 0;
}
int strcmp_insensitive(char *str1, const char *str2) {
    if(strlen(str1)!=strlen(str2))   //if they are different sizes then they can't match.
        return -1;  // Non-0 implementation is different so -1 is the default non-equal value.

    for(int i=0; i<strlen(str1); i++) {
        if(tolower(str1[i])!=tolower(str2[i]))
            return -1;
    }
    return 0;
}

vehicle* read_entry(FILE *file_ptr) {
    vehicle *entry=malloc(sizeof(vehicle));
    entry->size=0;
    entry->year=0;

    fread(&entry->size, 8, 1, file_ptr);    //sizeof(long) is 4 so cant use sizeof
    int begin=ftell(file_ptr);
    fread(&entry->year, 4, 1, file_ptr);    //sizeof(int) is also 4

    entry->make=read_next_str(file_ptr);    //three middle strings
    entry->model=read_next_str(file_ptr);
    entry->color=read_next_str(file_ptr);


    int str_begin=ftell(file_ptr);
    int bits_left=(begin+entry->size)-str_begin;

    entry->license_plate=calloc(bits_left+1, sizeof(char)); //last string is different since it has no null terminator.
    fread(entry->license_plate, sizeof(char), bits_left, file_ptr);
    entry->license_plate[bits_left]=0;

    return entry;
}
char* read_next_str(FILE *file_ptr) {
    char *str=NULL;

    int str_begin=ftell(file_ptr);
    while(fgetc(file_ptr));
    int str_end=ftell(file_ptr);
    fseek(file_ptr, str_begin, SEEK_SET);

    str=calloc(str_end-str_begin, sizeof(char));
    fread(str, sizeof(char), str_end-str_begin, file_ptr);
    
    return str;
}

void add_entry(dynamic_array *data_array, vehicle *data) {
    data_array->size++; //increases size.
    data_array->data=realloc(data_array->data, sizeof(vehicle*)*data_array->size); //reallocates memory.

    data_array->data[data_array->size-1]=data;  //inserts data.
}

void free_array(dynamic_array *data_array) {
    for(int i=0; i<data_array->size; i++) {
        free(data_array->data[i]);
    }
    free(data_array);
}

void print_entry(vehicle *data) {
    printf("%d %s %s (%s) LIC#%s\n", data->year, data->make, data->model, data->color, data->license_plate);
}
void print_array(dynamic_array *data_array) {
    if(data_array->size==0) {
        printf("No entries matched your search.\n");
        return;
    }

    for(int i=0; i<data_array->size; i++) {
        print_entry(data_array->data[i]);
    }
}

/* Searches for a given term in a file and prints the data of the appropriate cars
 *
 * ./a.out FILENAME TERM
 */
int main(int argc, const char **argv) {

    if (argc!=3) {
        printf("USAGE: ./a.out FILENAME TERM");
        return 1;
    }

    FILE *file_ptr = fopen(argv[1], "rb");  //opens file and exits if not found.
    if(file_ptr==NULL) {
        printf("\"%s\" could not be found. Exiting program.", argv[1]);
        return 1;
    }
    char file_type[STR_BUFF];
    strcpy(file_type, strchr(argv[1], '.'));
    if(strcmp(file_type, ".db")) {  //determines whether the file type is correct.
        printf("Invalid file type. Exiting program.");
        return 0;
    }

    dynamic_array *data=malloc(sizeof(dynamic_array));
    data->size=0;
    data->data=NULL;

    while(!feof(file_ptr)) {
        fseek(file_ptr, -1, SEEK_CUR);  //resets pointer location if EOF is not read.

        vehicle *limbo_entry = read_entry(file_ptr);    //limbo_entry will either be killed or will survive depending on whether it has the term or not.
        if(search_entry(limbo_entry, argv[2]))
            add_entry(data, limbo_entry);
        else
            free(limbo_entry);

        fgetc(file_ptr);    //tests the next bit to see if its the EOF
    }
    fclose(file_ptr);

    print_array(data);
    free_array(data);   //frees data and everything inside it.

    return 1;
}
