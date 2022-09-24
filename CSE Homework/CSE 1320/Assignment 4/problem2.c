#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problem2.h"

#define STR_BUFF 128

void insert(dynamic_array *arr) {
    char buff[STR_BUFF];

    printf("Enter a number: ");
    fgets(buff, STR_BUFF, stdin);
    double num=atof(buff);


    arr->size++;
    double *new_ptr=malloc(sizeof(double)*arr->size);    //get new memory.
    

    for(int i=0; i<arr->size-1;i++) {    //moves old data to a new pointer with available space. realloc would be usefull but doesnt have new space at the beginning. Maybe if i had the array in reverse order, but thats needlessly confusing.
        new_ptr[i+1]=arr->data[i];
    }
    new_ptr[0]=num;
    printf("%.3f added at index 0, array size is %d.\n", num, arr->size);

    free(arr->data); //frees old array.
    arr->data=new_ptr;   //reinitilize array.
}
void delete(dynamic_array *arr) {
    char buff[STR_BUFF];

    printf("Enter an index: ");
    fgets(buff, STR_BUFF, stdin);
    int index=atoi(buff);

    if(index<0||index>arr->size-1) {    //cheching if the input is in range.
        printf("Invalid index. Try again.\n");
        delete(arr);    //recursively asks if needed.
        return;
    }

    arr->size--;
    double *new_ptr=malloc(sizeof(double)*arr->size);   //allocating new memory.

    for(int i=0; i<index; i++) {  //copying first half of data
        new_ptr[i]=arr->data[i];
    }
    for(int i=index; i<arr->size; i++) {  //copying second half of data
        new_ptr[i]=arr->data[i+1];
    }

    printf("%.3f removed from index %d, array size is %d.\n", arr->data[index], index, arr->size);

    free(arr->data);
    arr->data=new_ptr;
}

void printCommands(char *arr[], int size) { //prints out a list of commands.
    for(int i=0; i<size; i++) {
        printf("%d. %s\n", i+1, arr[i]);
    }
}
int getCommand(int commands) {    //gets the selected number from the user.
    char buff[STR_BUFF];

    printf("> ");
    fgets(buff, STR_BUFF, stdin);
    int num=atoi(buff); // if the input isn't a number, there is undefined behavior. 
                        //Doesn't cause a problem since 0 is the default value and gets caught later. 
                        //"2hello" would still work even though it isn't entirely a number.
    
    if(num<1||num>commands) {
        printf("Invalid command. Try again.\n");
        return getCommand(commands);    //recursivly asks if needed.
    }
    return num;
}
void printData(dynamic_array *arr) { //debug method
    for(int i=0; i<arr->size; i++) {
        printf("%d: %.3f\n", i, arr->data[i]);
    }
}

int main() {
    dynamic_array *numbers=malloc(sizeof(double*)+sizeof(int));
    numbers->data=NULL;
    numbers->size=0;

    char *commands[]={"Add Value","Remove Value","Exit"};
    int cmd_size=sizeof(commands)/sizeof(*commands);

    int command=0;
      
     while(1) { //assuming the exit command is last.
        printCommands(commands,cmd_size);
        command = getCommand(cmd_size);

        switch(command) {
            case 1: 
                insert(numbers);
                break;
            case 2: 
                delete(numbers);
                break;
            case 3:
                printf("Bye!");
                free(numbers->data);
                return 1;
        }
    }
}
