/* Coding Assignment 2
   Name: Landon Moon
   ID: 1001906270 
   
   README: program runs within requirements.
   -At compile time define "PERCENT" to show a percentage while sorting.
   -Showing the Percentage has a small effect on the tic time of the sort.
   -Percentage is useful for large files. Shows the progress.
   */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BUFF_SIZE 32

long fileSize(FILE *file_ptr)
{
    long int pos = ftell(file_ptr); // saves location
    fseek(file_ptr, 0, SEEK_SET);   // set to beginning of the file.

    long lines = 0;
    char str[BUFF_SIZE]; // never actually used.
    while (fgets(str, BUFF_SIZE, file_ptr))
    {
        lines++;
    }
    return lines;

    fseek(file_ptr, pos, SEEK_SET); // reset to last location.
}
int *inputFile(FILE *file_ptr, int lines)
{
    long int pos = ftell(file_ptr); // saves location
    fseek(file_ptr, 0, SEEK_SET);   // set to beginning of the file.

    int i = 0;
    char str[BUFF_SIZE];
    int *arr = malloc(sizeof(int) * lines);
    while (fgets(str, BUFF_SIZE, file_ptr))
    {
        arr[i] = atoi(str);
        i++;
    }

    fseek(file_ptr, pos, SEEK_SET); // reset to last location.
    return arr;
}
void printArr(int arr[], int size)
{
    int i = 0;
    for (; i < size; i++)
    {
        printf("%d\n", arr[i]);
    }
}
void insertionSort(int arr[], long size)
{
#ifdef PERCENT // define PERCENT if you want a progress bar.
    double percentDone, lastPercent = 0.0;
#endif

    int key;
    long j;
    long i = 1;
    for (; i < size; i++)
    {
        key = arr[i];

        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;

#ifdef PERCENT
        percentDone = ((double)i / size) * 100; // added a meter so we know the program is actually working and not hung
        if (percentDone - lastPercent >= .01)
        {
            printf("\r");
            printf("Sorting: %6.2f%% complete", percentDone);
            fflush(stdout);
            lastPercent = percentDone;
        }
#endif
    }
}

int main(int argc, const char **argv)
{
    clock_t start, end;

    if (argc != 2) // checks if argv[1] exists.
    {
        printf("USAGE: ./a.out FILENAME\n");
        return 1;
    }

    FILE *file_ptr = fopen(argv[1], "r"); // opens file and exits if not found.
    if (file_ptr == NULL)
    {
        printf("\"%s\" could not be found. Exiting program.\n", argv[1]);
        return 1;
    }

    long size = fileSize(file_ptr);
    int *arr = inputFile(file_ptr, size); // loads the file into memory. needs to be freed.

#ifdef PRINTARRAY
    printArr(arr, size);
    printf("\n\n");
#endif

    start = clock();
    insertionSort(arr, size);
    end = clock();

#ifdef PERCENT // define PERCENT if you want a progress bar.
    printf("\r");
    printf("Sorting: 100.00%% complete\n");
#endif

#ifdef PRINTARRAY
    printArr(arr, size);
    printf("\n\nProcessed %ld records\n", size);
#endif

    printf("Insertion Sort Tics = %ld\n", end - start);
    free(arr);
    fclose(file_ptr);
    return 0; /* return 0 if successful*/
}
