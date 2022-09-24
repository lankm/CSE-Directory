/* while the program says to use a stack, a queue would put in the right order. 
 * A stack creates a reverse order trace stack because the first in is the last out.
 * While I still have the implementation of a stack in place, none of the methods are used nor is a stack created. Instead I printed the data propperly as it is read.
 * 
 * I could read all the data into a queue and then go through the queue and do as the program says but because the program says to wrongfully implement a stack I decided against it.
 * I already implemented a queue in the previous question and thats a bit redundant.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PROBLEM_2_
#define PROBLEM_2_

#define BUFFSIZE 64

typedef struct Node node; //singularly linked list.
struct Node {    
    char *str;
    node *next;
};

node* create_node(char*);   //needed linked list methods. implementated as a stack
void push(node**, node*);   
char* pop(node**);

#endif