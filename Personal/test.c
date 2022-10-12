#include "ll.h"
#include <stdio.h>

void printValue(int i, void* v)
{
    printf("%f", *(double*)v);
}
void freeValue() {
    
}

int main()
{
    NODE* head = NULL;

    double num1 = 1;
    double num2 = 2;
    double num3 = 3;

    pushValue(&num1, &head);
    pushValue(&num2, &head);
    pushValue(&num3, &head);

    printList(&head, printValue);
    freeList(&head, NULL);
}
