/* Coding Assignment 3
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

int inputFile(int **arr, int argc, const char **argv)
{
    if (argc != 2) // checks if argv[1] exists.
    {
        printf("USAGE: ./a.out FILENAME\n");
        return -1;
    }
    FILE *file_ptr = fopen(argv[1], "r"); // opens file and exits if not found.
    if (file_ptr == NULL)
    {
        printf("\"%s\" could not be found. Exiting program.\n", argv[1]);
        return -1;
    }

    int lines = 0;                          //gets length of file
    char str[BUFF_SIZE];
    while (fgets(str, BUFF_SIZE, file_ptr))
    {
        lines++;
    }
    fseek(file_ptr, 0, SEEK_SET);

    int i = 0;                              //inputs file.
    *arr = malloc(sizeof(int) * lines);
    while (fgets(str, BUFF_SIZE, file_ptr))
    {
        (*arr)[i] = atoi(str);
        i++;
    }
    
    fclose(file_ptr);   //this closes the file after it has been input. This is not used to return the pointer back to the start.
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

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) // copy left array
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++) // copy right array
        R[j] = arr[m + 1 + j];

    i = 0; // start at beginning of arrays
    j = 0;
    k = l; // start of merged array
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    { // Left Array
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    { // Right Array
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main(int argc, const char **argv)
{
    clock_t start_I, end_I, start_M, end_M;

    int *arr = NULL;
    int size = inputFile(&arr, argc, argv); // loads the file into memory. needs to be freed.
    if(size==-1)
        return 1;

#ifdef PRINTARRAY
    printArr(arr, size);
    printf("\n\n");
#endif
    start_M = clock();
    mergeSort(arr, 0, size - 1);
    end_M = clock();
#ifdef PERCENT // this only prints after merge sort. since merge sort is recursive its more difficult to add a progress bar.
    printf("\r");
    printf("Sorting: 100.00%% complete\n\n\n");
#endif
#ifdef PRINTARRAY
    printArr(arr, size);
    printf("\n\n");
#endif

    free(arr);
    size = inputFile(&arr, argc, argv); // resets array
    if(size==-1)
        return 1;

#ifdef PRINTARRAY
    printArr(arr, size);
    printf("\n\n");
#endif
    start_I = clock();
    insertionSort(arr, size);
    end_I = clock();
#ifdef PERCENT // define PERCENT if you want a progress bar.
    printf("\r");
    printf("Sorting: 100.00%% complete\n\n\n");
#endif
#ifdef PRINTARRAY
    printArr(arr, size);
    printf("\n\n");
#endif


    printf("Processed %d records\n", size);
    printf("Merge Sort     = %ld\n", end_M - start_M);
    printf("Insertion Sort = %ld\n", end_I - start_I);
    
    free(arr);
    return 0; /* return 0 if successful*/
}
