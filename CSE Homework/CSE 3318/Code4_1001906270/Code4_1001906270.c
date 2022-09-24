/* Coding Assignment 4
   Name: Landon Moon
   ID: 1001906270
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 32

int inputFile(int **arr, int argc, const char **argv)
{
    if (argc < 2) // checks if argv[1] exists.
    {
        printf("USAGE: ./a.out FILENAME RUNS\n");
        return -1;
    }
    FILE *file_ptr = fopen(argv[1], "r"); // opens file and exits if not found.
    if (file_ptr == NULL)
    {
        printf("\"%s\" could not be found. Exiting program.\n", argv[1]);
        return -1;
    }

    int lines = 0; // gets length of file
    char str[BUFF_SIZE];
    while (fgets(str, BUFF_SIZE, file_ptr))
    {
        lines++;
    }
    fseek(file_ptr, 0, SEEK_SET);

    int i = 0; // inputs file.
    *arr = malloc(sizeof(int) * lines);
    while (fgets(str, BUFF_SIZE, file_ptr))
    {
        (*arr)[i] = atoi(str);
        i++;
    }

    fclose(file_ptr); // this closes the file after it has been input. This is not used to return the pointer back to the start.
    return lines;
}
void printArr(int arr[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition (int arr[], int low, int high)
{
    #if QSM 
        int middle = (high+low)/2; 
        swap(&arr[middle], &arr[high]); 
    #elif QSRND 
        int random = (rand()%(high-low+1)) + low;  
        swap(&arr[random], &arr[high]); 
    #endif
    
    int pivot = arr[high]; // right pivot. changed by conditional compiles before-hand.
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
 
    int j = low;//C99 Mode
    for (; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int splt = partition(arr, low, high);
 
        quickSort(arr, low, splt - 1);
        quickSort(arr, splt + 1, high);
    }
}

int main(int argc, const char **argv)
{
    clock_t start, end, total=0;

    int *arr = NULL;
    int size = inputFile(&arr, argc, argv); // loads the file into memory. needs to be freed.
    if (size == -1) //please just let me error handle in main please.
        return 1;

    int runs=0;
    if(argc<3)
        runs=10;
    else
        runs=atoi(argv[2]);

    int i = 0; //C99 mode
    for (; i < runs; i++)
    {
        #ifdef PRINTARRAY
            printArr(arr, size);
            printf("\n\n");
        #endif

        start = clock();
        quickSort(arr, 0, size - 1);
        end = clock();

        total+=end-start;
        printf("Run %d complete : %ld tics\n", i+1, end - start);

        #ifdef PRINTARRAY
            printArr(arr, size);
            printf("\n\n");
        #endif

        free(arr);  //resetting the array
        inputFile(&arr, argc, argv);
    }
    free(arr);

    printf("The average run time for %d runs is %ld\n\n\n", runs, total/runs);
    printf("Processed %d records\n", size);
    
    return 0; /* return 0 if successful*/
}
