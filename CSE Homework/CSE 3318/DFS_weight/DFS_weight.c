/* DFS_weight
   Name: Landon Moon
   ID: 1001906270
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define BUFF_SIZE 32

typedef struct _node NODE;
typedef struct _vert VERT;
struct _node /* linked list struct (stack) */
{
	int v; /* verts index */
    int w; /* weight */
	struct _node *next_ptr;
};
struct _vert /* vertex struct */
{
	int dist;
	struct NODE *head;
};

void add_node(NODE **head, int v, int w, VERT verts[])
{
    NODE *n = malloc(sizeof(NODE));
    n->v = v;
    n->w = w;

    n->next_ptr=*head;
    *head=n;
}

int count_v(FILE *file_ptr) //checks for largest vertex number; assumes no numbers are skipped. redo later.
{
    int count=0;

    int v1=0, v2=0;
    while (fscanf(file_ptr, "%d %d %*d", &v1, &v2) != EOF)
    {
        v1=v1>v2?v1:v2;
        count=v1>count?v1:count;
    }
    fseek(file_ptr, 0, SEEK_SET);
    return count;
}
void input_file(FILE *file_ptr, VERT verts[], int size)
{
    int i=0;
    for(;i<size;i++)
    {
        verts[i].dist=-1;
        verts[i].head=NULL;
    }

    int v1=0, v2=0, w=-1;
    while (fscanf(file_ptr, "%d %d %d", &v1, &v2, &w) != EOF)
        add_node((NODE**)&verts[v1].head, v2, w, verts);    /* casting isn't required. Gives warning without it */
}

void print_ll(NODE *head)
{
    while(head != NULL)
    {
        printf("(%d,%d),", head->v, head->w);
        head = head->next_ptr;
    }
    printf("\b \n");
}
void print_adj_l(VERT verts[], int size)
{
    int i=0;
    for(;i<size;i++)
    {
        printf("[%d]->", i);
        print_ll((NODE*)verts[i].head); /* casting isn't required. Gives warning without it */
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

    int count = count_v(file_ptr);
    VERT verts[count];  /* creates space for vertexies */
    input_file(file_ptr, verts, count);
    
    print_adj_l(verts, count);
    //printf("%d\n", verts[0].dist);

    return 0; /* return 0 if successful */
}
