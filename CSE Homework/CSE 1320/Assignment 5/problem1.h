#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef PROBLEM_1_
#define PROBLEM_1_

#define STR_BUFF 256

typedef struct {
    long size;
    int year;
    char *make;
    char *model;
    char *color;
    char *license_plate;
} vehicle;

typedef struct {
    int size;
    vehicle** data; //array of vehicle*
} dynamic_array;

/* Searches a given vehicle for a variable that matches the string. Is not case sensative.
 * "ford" and "for" would not match because "for" is a substring of "ford".
 *
 * Additionally searches whether the integer values of  year matches the given string by converting the value to a string then comparing.
 * Similarly "1999" and "199" would not match because "199" is a substring of "1999".
 * 
 * 
 * Returns a boolean value: 1 if a term matches and 0 if not.
 */ 
int search_entry(vehicle*, const char*);
/* mostly same implementation as strcmp except it is not case sensative.
 *
 * 0 means they are equal. Anything other than 0 means they are different. Non-0 return values are instead returned only as -1.
 */
int strcmp_insensitive(char*, const char*);

/* Reads the next car entry and returns a pointer to the generated car struct. assumes FILE* is at the beginning of the next set of data.
 * 
 * The returned pointer should be treated as a posible valid car. This validity is determined by using search_entry.
 * If search_entry returns 0, the struct should immediely be freed as to only allocate memory for requested data.
 */
vehicle* read_entry(FILE*);
/* for reading the 3 strings that have a null terminator in the file.
 */
char* read_next_str(FILE*);

/* Adds a car struct to the end of a dynamic array of car*. Returns the pointer to the new array.
 */
void add_entry(dynamic_array*, vehicle*);


/* given a dynaic array of vehicle*, frees all data contained within the array and within each car struct along with the array itself.
 */
void free_array(dynamic_array*);

/* Prints the data from one entry.
 */
void print_entry(vehicle*);
/* Prints the data from each entry in the array in propper format
 */
void print_array(dynamic_array*);

#endif
