/* I did less input verification than I normally would. entering a string as a year is counted as 0 and doesn't ask again.
 * string lengths in the vehicle struct are always BUFFSIZE. I could shorten them to save memory but i'm tired and don't want to. It isn't required.
 * Queue implementation of the linked list could include a *last variable in a separate struct to make it more effiecient.
 * 
 * The program runs exactly as instructed, its just not necisarrily up to my normal standards.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROBLEM_1_
#define PROBLEM_1_

#define BUFFSIZE 64

typedef struct {
    int year;
    char *make;
    char *model;
    char *color;
    char *license_plate;
} vehicle;

typedef struct Node node; //singularly linked list. 
struct Node{    
    vehicle *data;
    node *next;
};

node* create_node(vehicle*);   //needed linked list methods. Treated as queue in implementation
void offer(node**, node*);
node* poll(node**);

void showList(char[][BUFFSIZE], int);  //IO methods.
void printn(node*);
char* getinput();

void addVehicle(node**);  //commands
void viewNextVehicle(node**);
void viewCurrentQueue(node**);
void quit();
void error();

vehicle* makeVehicle();
void freequeue(node**); //data relieving

#endif
