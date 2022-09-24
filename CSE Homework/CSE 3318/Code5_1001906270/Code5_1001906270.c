/* Code5_1001906270
   Name: Landon Moon
   ID: 1001906270
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define BUFF_SIZE 32

typedef struct
{
    char label[6];
    int distance;
    int previous;
    int visited;
} Vertex;

int fileLength(FILE *file_ptr)
{
    int count = 0;
    char c;
    while ((c = fgetc(file_ptr)) != -1) /* Double check file format with proff */
    {
        if (c == '\n')
            count++;
    }
    fseek(file_ptr, 0, SEEK_SET);
    return count;
}
void fileInput(FILE *file_ptr, int count, int adj[][count], Vertex v[]) /* populates arr and returns the # of verticies */
{
    int i = 0;
    for (; i < count; i++) /* initilize the array */
    {
        int j = 0;
        for (; j < count; j++)
        {
            adj[i][j] = -1;
        }
    }

    char buf1[BUFF_SIZE];
    char *buf2;
    i = 0;
    for (; i < count; i++)
    {
        fgets(buf1, BUFF_SIZE, file_ptr);

        strcpy(v[i].label, strtok(buf1, ",")); /* v init */
        v[i].distance = INT_MAX;
        v[i].previous = -1;
        v[i].visited = 0;

        while ((buf2 = strtok(NULL, ",")) != NULL) /* adj init */
        {
            int to = atoi(buf2);
            int weight = atoi(strtok(NULL, ","));
            adj[i][to] = weight;
        }
    }
}

int labelIndex(Vertex v[], char str[], int count)
{
    str = strtok(str, " \n"); /* using strtok as a trim funciton */
    int index = -1;
    int i = 0;
    for (; i < count; i++)
    {
        if (strcmp(str, v[i].label) == 0)
            index = i; // would return here but not allowed;
    }
    return index;
}
void dijkstra(int count, Vertex v[], int adj[][count], int start)
{
    int cv = start; // current vertex
    v[cv].distance = 0;
    v[cv].visited = 1;

    int x, i, adjnum, nextval;
    for (x = 0; x < count - 1; x++)
    {
        for (i = 0; i < count; i++) /* relaxing edges */
        {
            adjnum=adj[cv][i];
            if(adjnum != -1 && v[i].distance>v[cv].distance+adjnum)
            {
                v[i].previous = cv;
                v[i].distance = v[cv].distance+adjnum;
            }
        }
        v[cv].visited=1;

        nextval=INT_MAX;
        for (i = 0; i < count; i++) /* looking for smallest vertex */
        {
            if(v[i].distance<nextval && v[i].visited==0)
            {
                nextval=v[i].distance;
                cv=i;
            }
        }
    }
    v[cv].visited=1; /* counts the last visited vertex as visited */
}
void printPath(Vertex v[], int end)
{
    if(v[end].previous == -1)
    {
        printf("%s->", v[end].label);
        return;
    }
    printPath(v,v[end].previous);
    printf("%s->", v[end].label);
}

void printAdj(int count, int adj[][count])
{
    int i = 0;
    for (; i < count; i++)
    {
        int j = 0;
        for (; j < count; j++)
        {
            printf("%3d ", adj[i][j]);
        }
        printf("\n");
    }
}
void printV(int count, Vertex v[])
{
    printf("%3s %6s %12s %3s %3s\n", "I", "L", "D", "P", "V");
    int i = 0;
    for (; i < count; i++)
    {
        printf("%3d %6s %12d %3d %3d\n", i, v[i].label, v[i].distance, v[i].previous, v[i].visited);
    }
}

int main(int argc, const char **argv)
{
    if (argc < 2) // checks if argv[1] exists.
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

    int count = fileLength(file_ptr);
    int adj[count][count];
    Vertex v[count];
    fileInput(file_ptr, count, adj, v); /* inits adj and v */

#ifdef PRINTIT
    printAdj(count, adj);
#endif

    char buf1[BUFF_SIZE];
    printf("What is the starting vertex? ");   /* input */
    fgets(buf1, BUFF_SIZE, stdin);
    int strt = labelIndex(v, buf1, count);

    dijkstra(count, v, adj, strt);

#ifdef PRINTIT
    printf("\n");
    printV(count, v);
#endif

    printf("What is the destination vertex? ");   /* input */
    fgets(buf1, BUFF_SIZE, stdin);
    int dest = labelIndex(v, buf1, count);

    printf("The path from %s to %s is ", v[strt].label, v[dest].label);
    printPath(v, dest);
    printf("\b\b and has a length of %d", v[dest].distance);

    return 0; /* return 0 if successful */
}
