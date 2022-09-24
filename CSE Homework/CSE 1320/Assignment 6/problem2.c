#include "problem2.h"

node* create_node(char *str) {   //needed linked list methods. implementated as a stack
    node *n = malloc(sizeof(node));
    n->str=malloc(BUFFSIZE);
    strcpy(n->str, str);
    n->next=NULL;

    return n;
}
void push(node **stack, node *n) {
    n->next=*stack;
    *stack=n;
} 
char* pop(node **stack) {
    node *n=*stack;
    *stack = (*stack)->next;

    char* str=n->str;
    free(n);
    return str;
}

int main(int argc, const char **argv) {
    if (argc!=2) {
        printf("USAGE: ./a.out FILENAME");
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");  //opens file and exits if not found.
    if(fp==NULL) {
        printf("\"%s\" could not be found. Exiting program.", argv[1]);
        return 1;
    }

    char file_type[BUFFSIZE];
    strcpy(file_type, strchr(argv[1], '.'));
    if(strcmp(file_type, ".txt")) {  //determines whether the file type is correct.
        printf("Invalid file type. Exiting program.");
        return 0;
    }

    
    //node **stack=malloc(sizeof(node*)); //while the program says to use a stack, a queue would put in the right order. a stack creates a reverse order trace stack.
    //*stack = NULL;    //more information about why I didn't use a stack in the header file documentation.

    int tabs=0;
    while(!feof(fp)) {
        char buff[BUFFSIZE];
        fgets(buff, BUFFSIZE, fp);

        if(!strcmp(buff, "return\n")) {
            tabs--;
        }
        else {
            for(int i=0; i<tabs; i++)
                printf("    ");
            printf("%s", buff);
            tabs++;
        }
    }
}
