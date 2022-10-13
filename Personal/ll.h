/* This header file implements a doubly linked list and some useful functions
 *
 * Author: Landon Moon
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef LL
#define LL

/* doubly linked list node */
typedef struct node
{
	void* value;

    struct node *last_ptr;
	struct node *next_ptr;
} NODE;

/* Returns a single node with the given value */
NODE* createNode(void* value)
{
	NODE *n = (NODE*) malloc(sizeof(NODE));
	n->value = value;
	n->last_ptr = NULL;
    n->next_ptr = NULL;

	return n;
}

/* Node functions. Generic, freeing and printing. args defined by forEachNode */
void node_fn_ptr(NODE* node, void (*value_fn_ptr)(int, void*), int i)
{
    // if not null then free value
    if(value_fn_ptr != NULL)
    {
        value_fn_ptr(i, node->value);
    }
}
void freeNode(NODE* node, void (*value_fn_ptr)(int, void*), int i)
{
    // freeing value
    node_fn_ptr(node, value_fn_ptr, -1);

    // freeing node
    free(node);
}
void printNode(NODE* node, void (*value_fn_ptr)(int, void*), int i)
{
    // printing the value given fun_value
    printf("%2d: value: ", i);
    node_fn_ptr(node, value_fn_ptr, i);

    // printing node data
    printf("\n     node: %p\n", node);
    printf("     next: %p\n", node->next_ptr);
    printf("     last: %p\n\n", node->last_ptr);
}

/* Executes fun_ptr on each node without popping (head, node_fn_ptr, value_fn_ptr) */
void forEachNode(NODE** head, void (*node_fn_ptr)(NODE*, void (*)(int, void*), int), void (*value_fn_ptr)(int, void*))
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
            node_fn_ptr(temp, value_fn_ptr, i);
            
            // resync temp
            temp = node;
            i++;
        }
        while(node != *head);
    }
}
void forEachVal(NODE** head, void (*value_fn_ptr)(int, void*))
{
    forEachNode(head, node_fn_ptr, value_fn_ptr);
}

/* frees and printing LL */
void freeList(NODE** head, void (*value_fn_ptr)(int, void*))
{
    forEachNode(head, freeNode, value_fn_ptr);
    *head = NULL;
}
void printList(NODE** head, void (*value_fn_ptr)(int, void*))
{
    forEachNode(head, printNode, value_fn_ptr);
}

/* adds a node to the tail */
void enqueue(NODE* node, NODE** head)
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
void enqueueValue(void* value, NODE** head)
{
    NODE* node = createNode(value);
    enqueue(node, head);
}

/* adds a node to the head */
void push(NODE* node, NODE** head)
{
    // common between stack and queue
    enqueue(node, head);

    // repointing the head to the new node
    *head = node;
}
void pushValue(void* value, NODE** head)
{
    NODE* node = createNode(value);
    push(node, head);
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
