// Coding Assignment 6 - Donna French - 100074079

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
 
#define HASHTABLESIZE 37
 
/* Node for storing information */
typedef struct Star
{ 
    char *name;      /* system name-star name */

    char class;             /* stellar class */
    float distance;         /* in light-years */
    float mass;             /* in solar masses */
    float abs_magnitude;    /* in Mv */
    int planets;            /* known planets */

    struct Star *next_ptr;
} 
STAR;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
	int HashIndex = 0;
	
	for (int i = 0; i < strlen(key); i++)
	{
		HashIndex += key[i];
	}
	
	return HashIndex %= HASHTABLESIZE; 
}

void AddNode(STAR *NewNode, STAR *Starmap[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (Starmap[HashIndex] == NULL) 
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		Starmap[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		STAR *TempPtr = Starmap[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(STAR *Starmap[])
{
	STAR *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = Starmap[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(STAR *Starmap[])
{
	char LookupName[100] = {};
	int result = 0;
	
	fgets(LookupName,100,stdin);
	printf("Enter the name of the Star to delete from the Starmap ");
	fgets(LookupName,100,stdin);

	LookupName[strlen(LookupName)-1]=0; //deletes extra newline on LookupName

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	STAR *TempPtr = Starmap[HashIndex];
	STAR *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nStar %s does not exist in the Starmap\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == Starmap[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					Starmap[HashIndex] = TempPtr->next_ptr;
					printf("\nStar %s has been deleted from the Starmap\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nStar %s has been deleted from the Starmap\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nStar %s does not exist in the Starmap\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(STAR *Starmap[])
{
	int i;
	STAR *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Starmap[i];

		printf("\nStarmap[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(STAR *Starmap[])
{
	int i;
	STAR *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Starmap[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByName(STAR *Starmap[])
{
	STAR *TempPtr = NULL;
	char height[10] = {};
	char feet[10] = {};
	char inches[10] = {};
	char LookupName[100] = {};
	int FoundIt = 0;
	
	fgets(LookupName,100,stdin);//clears stdin
	printf("\n\nEnter Star's name ");
	fgets(LookupName,100,stdin);
	LookupName[strlen(LookupName)-1]=0; //deletes extra newline on LookupName
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = Starmap[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;

					printf("\n");
					printf("Name\t\t\t\t%s\n", TempPtr->name);
					printf("Class\t\t\t\t%c\n", TempPtr->class);
					printf("Distance\t\t\t%.2f Ly\n", TempPtr->distance);
					printf("Mass\t\t\t\t%.2f Solar masses\n", TempPtr->mass);
					printf("Abs Magnitude\t\t\t%.2f\n", TempPtr->abs_magnitude);
					printf("# of known planets\t\t%d\n", TempPtr->planets);
					

				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nStar %s not found in Starmap\n\n", LookupName);
}

void AddNewStar(STAR *Starmap[])
{
	int HashIndex = 0;
	STAR *NewNode;
	char TempBuffer[100] = {};

	NewNode = malloc(sizeof(STAR));
	NewNode->next_ptr = NULL;

	fgets(TempBuffer,100,stdin);//clears stdin
	printf("\n\nEnter new Star's name ");
	fgets(TempBuffer,100,stdin);
	TempBuffer[strlen(TempBuffer)-1]=0; //deletes extra newline on LookupName

	NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

	printf("\n\nEnter %s's Class as a letter ", NewNode->name);
	fgets(TempBuffer,100,stdin);
	NewNode->class=TempBuffer[0];
	
	printf("\n\nEnter %s's distance in Ly ", NewNode->name);
	scanf("%f", &(NewNode->distance));
	
	printf("\n\nEnter %s's mass ", NewNode->name);
	scanf("%f", &(NewNode->mass));

	printf("\n\nEnter %s's absolute magnitude ", NewNode->name);
	scanf("%f", &(NewNode->abs_magnitude));

	printf("\n\nEnter %s's number of known planets ", NewNode->name);
	scanf("%d", &(NewNode->planets));

	AddNode(NewNode, Starmap);
}

int ReadFileIntoHashTable(int argc, char *argv[], STAR *Starmap[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
	STAR *NewNode;

	if (argc > 1)
	{
		FH = fopen(argv[1], "r");

		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
			token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(STAR));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
			NewNode->class = token[0];
			
			token = strtok(NULL, "|");
			NewNode->distance = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->mass = atof(token);
			
			token = strtok(NULL, "|");
			NewNode->abs_magnitude = atof(token);

			token = strtok(NULL, "|");
			NewNode->planets = atoi(token);

			AddNode(NewNode, Starmap);

			counter++;
		}

	}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{
	int MenuChoice = 0;
	int counter = 0;
	STAR *Starmap[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	counter = ReadFileIntoHashTable(argc, argv, Starmap);
 
	do
	{
		printf("\n\nStarmap Menu\n\n"
			   "1. Show all Stars in Starmap for a given letter\n"
			   "2. Look up Stars by name\n"
			   "3. How many Stars are in the Starmap?\n"
			   "4. Display the Starmap\n"
			   "5. Add a new Star\n"
			   "6. Delete a Star from the Starmap\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
				ShowByLetter(Starmap);
				break;
			case SHOWBYNAME:
				ShowByName(Starmap);
				break;
			case COUNT:
				printf("Your Starmap contains %d star\n", counter); 
				break;
 			case DISPLAY:
				DisplayHashTable(Starmap);
				break;
			case ADD:
				AddNewStar(Starmap);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(Starmap))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(Starmap);

	return 0;
}			  
