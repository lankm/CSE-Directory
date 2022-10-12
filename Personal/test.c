#include "ds.h"
#include <stdio.h>

void fun_ptr(void* v)
{
    printf("%d\n", *(int*)v);
}

int main()
{
    NODE* head = NULL;

    int num1 = 17;
    int num2 = 12;
    int num3 = 15;

    stackPushValue(&num1, &head);
    stackPushValue(&num2, &head);
    stackPushValue(&num3, &head);
    stackPushValue(&num2, &head);
    stackPushValue(&num3, &head);

    freeList(&head, fun_ptr);

    if(head == NULL)
        printf("NULL\n");
}
/*  // if empty then do nothing
    if(*head == NULL);
    else
    {
        // current and temp nodes
        NODE* node = *head;
        NODE* temp = node;

        // loop until head is read
        do
        {
            // free node and increment
            node = node->next_ptr;
            freeNode(temp, fun_freeValue);
            
            // resync temp
            temp = node;
        }
        while(node != *head);

        // set to null for safety reasons
        *head = NULL;
    } */