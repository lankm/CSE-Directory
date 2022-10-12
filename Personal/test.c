#include "ds.h"
#include <stdio.h>

void printValue(int i, void* v)
{
    printf("%d: %d\n", i, *(int*)v);
}

int main()
{
    NODE* head = NULL;

    int num1 = 1;
    int num2 = 2;
    int num3 = 3;

    stackPushValue(&num1, &head);
    stackPushValue(&num2, &head);
    stackPushValue(&num3, &head);
    stackPushValue(&num2, &head);
    stackPushValue(&num3, &head);

    forEachVal(&head, printValue);
}
