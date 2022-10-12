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

/* node function. i is a index if applicable */
void fun_node(NODE* node, void (*fun_value)(int, void*), int i)
{
    // if not null then free value
    if(fun_value != NULL)
    {
        fun_value(i, node->value);
    }
}
/* node function. frees the given node and value with the funciton pointer. i is not used */
void freeNode(NODE* node, void (*fun_freeValue)(int, void*), int i)
{
    // freeing value
    fun_node(node, fun_freeValue, -1);

    // freeing node
    free(node);
}
/* node function. prints each value of a node */
void printNode(NODE* node, void (*fun_value)(int, void*), int i)
{
    // printing the value given fun_value
    printf("%2d: value: ", i);
    fun_node(node, fun_value, i);

    // printing node data
    printf("\n     node: %p\n", node);
    printf("     next: %p\n", node->next_ptr);
    printf("     last: %p\n\n", node->last_ptr);
}

/* executes fun_ptr on each node without popping (head, node_function, value_function) */
void forEachNode(NODE** head, void (*fun_node)(NODE*, void (*)(int, void*), int), void (*fun_value)(int, void*))
{
    // if empty then do nothing
    if(*head == NULL);
    else
    {
        // current and temp nodes
        NODE* node = *head;
        NODE* temp = node;

        // loop until head is read
        int i=0;
        do
        {
            // increment and execute function
            node = node->next_ptr;
            fun_node(temp, fun_value, i);
            
            // resync temp
            temp = node;
            i++;
        }
        while(node != *head);
    }
}
void forEachVal(NODE** head, void (*fun_value)(int, void*))
{
    forEachNode(head, fun_node, fun_value);
}

/* frees the entire linked list */
void freeList(NODE** head, void (*fun_freeValue)(int, void*))
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

/* peek and pop */
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
void* pop(NODE** head, void (*fun_freeValue)(int, void*))
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
    freeNode(node, fun_freeValue, -1);
    printf("freed %p\n", node);
    return value;
}

#endif
