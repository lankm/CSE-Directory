/* This header file implements multiple types of data structures in c.
 *
 * Author: Landon Moon
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef DS
#define DS

/* doubly linked list node */
typedef struct node
{
	void* value;

    struct node *last_ptr;
	struct node *next_ptr;
} NODE;

/* returns a single node with the given value */
NODE* createNode(void* value)
{
	NODE *n = (NODE*) malloc(sizeof(NODE));
	n->value = value;
	n->last_ptr = NULL;
    n->next_ptr = NULL;

	return n;
}
/* frees the given node and value with the funciton pointer */
void freeNode(NODE* node, void (*fun_freeValue)(void*))
{
    // if not null then free value
    if(fun_freeValue != NULL)
    {
        fun_freeValue(node->value);
    }

    free(node);
}
/* function for a node with only the value function*/ //add index value that is passed in.
void fun_node(NODE* node, void (*fun_value)(void*))
{
    // if not null then free value
    if(fun_value != NULL)
    {
        fun_value(node->value);
    }
}

/* executes fun_ptr on each node without popping */
void forEachNode(NODE** head, void (*fun_node)(NODE*, void (*)(void*)), void (*fun_value)(void*))
{
    // if empty then do nothing
    if(*head == NULL);
    else
    {
        // current and temp nodes
        NODE* node = *head;
        NODE* temp = node;

        // loop until head is read
        do
        {
            // increment and execute function
            node = node->next_ptr;
            fun_node(temp, fun_value);
            
            // resync temp
            temp = node;
        }
        while(node != *head);
    }
}
void forEachVal(NODE** head, void (*fun_value)(void*))
{
    forEachNode(head, fun_node, fun_value);
}

/* frees the entire linked list */
void freeList(NODE** head, void (*fun_freeValue)(void*))
{
    forEachNode(head, freeNode, fun_freeValue);
    *head = NULL;
}

/* adds a node to the tail */
void queuePush(NODE* node, NODE** head)
{
    // if empty
    if(*head == NULL)
    {
        // implemented as a circular LL
        node->next_ptr = node;
        node->last_ptr = node;

        // inserting beginning node
        *head=node;
    }
    else
    {   // temp variable for swapping
        NODE* tail = (*head)->last_ptr;

        // tail --- node <-> head
        node->next_ptr = *head;
        (*head)->last_ptr = node;

        // tail <-> node --- head
        node->last_ptr = tail;
        tail->next_ptr = node;
    }
}
void queuePushValue(void* value, NODE** head)
{
    NODE* node = createNode(value);
    queuePush(node, head);
}

/* adds a node to the head */
void stackPush(NODE* node, NODE** head)
{
    // common between stack and queue
    queuePush(node, head);

    // repointing the head to the new node
    *head = node;
}
void stackPushValue(void* value, NODE** head)
{
    NODE* node = createNode(value);
    stackPush(node, head);
}

/* views the head */
void* peek(NODE* head)
{
    // if empty
    if(head == NULL)
    {
        return NULL;
    }
    else
    {
        return head->value;
    }
}
/* peeks and then pops */
void* pop(NODE** head, void (*fun_freeValue)(void*))
{
    // temp variables for swapping, freeing, and returning
    NODE* new_head = (*head)->next_ptr;
    NODE* node = *head;
    void* value = node->value;

    // if only has one node
    if(new_head == *head)
    {
        *head = NULL;
    }
    else
    {
        // tail <-> head
        new_head->last_ptr = (*head)->last_ptr;
        (*head)->last_ptr->next_ptr = new_head;

        // moving head to new_head
        *head = new_head;
    }

    // freeing and returning
    freeNode(node, fun_freeValue);
    printf("freed %p\n", node);
    return value;
}

#endif
