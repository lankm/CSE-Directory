/* Coding Assignment 1
   Name: Landon Moon
   ID: 1001906270 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 32

typedef struct node
{
	int number;
	struct node *next_ptr;
} NODE;

NODE *CreateNode(int Number)
{
	NODE *n = malloc(sizeof(NODE));
	n->number = Number;
	n->next_ptr = NULL;

	return n;
}
void AddNodeToLL(int Number, NODE **LinkedListHead) /* treat LL as a queue. Inefficient */
{
	if (*LinkedListHead == NULL)			  /* if no node to mount to */
		*LinkedListHead = CreateNode(Number); // CreateNode uses malloc. required as part of ruberic.
	else
	{
		NODE *tail = *LinkedListHead;
		while (tail->next_ptr != NULL) /* traverses to end of LL */
			tail = tail->next_ptr;

		NODE *n = CreateNode(Number);
		tail->next_ptr = n;
	}
}

void ReadFileIntoLL(int argc, const char **argv, NODE **LLH)
{
	if (argc != 2) // checks if argv[1] exists.
	{
		printf("USAGE: ./a.out FILENAME\n");
		exit(1); // wish I could change the funtion parameters to change this.
	}

	FILE *file_ptr = fopen(argv[1], "r"); // opens file and exits if not found.
	if (file_ptr == NULL)
	{
		printf("\"%s\" could not be found. Exiting program.\n", argv[1]);
		exit(1);
	}

	int i = 0;
	int total = 0;

	char str[BUFF_SIZE];
	while (fgets(str, BUFF_SIZE, file_ptr))
	{
		int Number = atoi(str);
		AddNodeToLL(Number, LLH);
		LLH = &((*LLH)->next_ptr); // changes the head of the LL so AddNodeToLL never traverses the LL

		i++;
		total += Number;
	}
	fclose(file_ptr);

	printf("%d records were read for a total of %d\n", i, total);
}

void PrintLLonly(NODE *LLH) // I wish I could do this an other way. printing the total with different messages requires this or a different return.
{
	while (LLH != NULL)
	{
		printf("0x%p %d ", LLH, LLH->number);
		if (LLH->next_ptr == 0)
			printf("(nil)\n");
		else
			printf("0x%p\n", LLH->next_ptr);

		LLH = LLH->next_ptr;
	}
}
void PrintLL(NODE *LLH)
{
	int i = 0;
	int total = 0;
	while (LLH != NULL)
	{
		printf("0x%p %d ", LLH, LLH->number);
		if (LLH->next_ptr == 0)
			printf("(nil)\n");
		else
			printf("0x%p\n", LLH->next_ptr);

		i++;
		total += LLH->number;

		LLH = LLH->next_ptr;
	}

	printf("%d records were read for a total sum of %d\n", i, total);
}

void FreeLL(NODE **LLH)
{
#ifdef PRINT
	PrintLLonly(*LLH);
#endif

	int i = 0;
	int total = 0;
	while (*LLH != NULL) //frees each node from head to tail.
	{
		i++;
		total += (*LLH)->number;

		NODE *next = (*LLH)->next_ptr;
		free(*LLH);
		*LLH = next;
	}

	printf("%d nodes were deleted for a total of %d\n", i, total);
}

int main(int argc, const char **argv)
{
	clock_t start, end;

	NODE *LLH = NULL;

	start = clock(); /* capture the clock in a start time */
	ReadFileIntoLL(argc, argv, &LLH);
	end = clock(); /* capture the clock in an end time */
	printf("%ld tics to write the file into the linked list\n", end - start);

#ifdef PRINT
	start = clock(); /* capture the clock in a start time */
	PrintLL(LLH);
	end = clock(); /* capture the clock in an end time */
	printf("%ld tics to print the linked list\n", end - start);
#endif

	start = clock(); /* capture the clock in a start time */
	FreeLL(&LLH);
	end = clock(); /* capture the clock in an end time */
	printf("%ld tics to free the linked list\n", end - start);

	return 0; /* return 0 if successful*/
}
