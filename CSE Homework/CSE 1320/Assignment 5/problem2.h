#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef PROBLEM_2_
#define PROBLEM_2_

#define STR_BUFF 256

typedef struct {
    int year;
    char *make;
    char *model;
    char *color;
    char *license_plate;
} vehicle;

typedef struct Node node; //singularly linked list.
struct Node{    
    void *data;
    node *next;
};

node* create_node(void*);   //needed linked list methods.
void add_node(node**, node*);
node* get_node(node**, int);

void free_list(node**, int); //method to free data.

void print_entry(node*);    //output
void print_entries(node**);
void print_make(node*);
void print_makes(node**);

void read_csv_token(char**, FILE*); //reading from file
vehicle* read_csv_line(FILE*);
node** read_csv_data(FILE*);

int strcmp_insensitive(char *, const char *);   //generating the list of makes
int contains_make(node**, char*);
node** generate_makes_list(node**);

char* make_input(node **);  //getting user input

node** generate_selection_list(node**,char*);   //generate list of selected vehicles.

#endif
