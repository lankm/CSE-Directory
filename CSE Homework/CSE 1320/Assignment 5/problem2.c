#include "problem2.h"

node* create_node(void *data) {
    node *n = malloc(sizeof(node));
    n->data=data;
    n->next=NULL;

    return n;
}
void add_node(node **head, node *new_node) {
    new_node->next=*head;
    *head=new_node;
}
node* get_node(node **head, int index) {
    node *n=*head;

    for(int i=0; i<index; i++) {
        n=n->next;
    }

    return n;
}

void free_list(node **head, int type) { //type:   0=vehicle list   1=string list
    node *cur=*head;

    while(1) {
        node *next=cur->next;

        if(type==0)
            free(cur->data);
        free(cur);
        
        
        if(next==NULL)
            break;
        else
            cur=next;
        
    }
    free(head);
}

void print_entry(node *n) {
    printf("%d %s %s (%s) LIC#%s", ((vehicle*)n->data)->year, 
                                     ((vehicle*)n->data)->make, 
                                     ((vehicle*)n->data)->model, 
                                     ((vehicle*)n->data)->color, 
                                     ((vehicle*)n->data)->license_plate);
}
void print_entries(node **head) {
    node *cur=*head;

    while(1) {
        print_entry(cur);
        printf("\n");

        if(cur->next==NULL)
            break;
        else
            cur=cur->next;
    }
}
void print_make(node *n) {
    printf("%s\n", (char*)(n->data));
}
void print_makes(node **head) {
    node *cur=*head;

    int i=1;
    while(1) {
        printf("%d. ", i++);
        print_make(cur);

        if(cur->next==NULL)
            break;
        else
            cur=cur->next;
    }
}

void read_csv_token(char **destination, FILE *fp) {
    char buff[STR_BUFF];
    strcpy(buff, strtok(NULL, ",\n"));
    *destination=calloc(strlen(buff), sizeof(char));
    strcpy(*destination, buff);
}
vehicle* read_csv_line(FILE *fp) {
    char line[STR_BUFF];
    fgets(line, STR_BUFF, fp);

    vehicle *entry=malloc(sizeof(vehicle));

    entry->year=atoi(strtok(line, ",\n"));
    read_csv_token(&(entry->make), fp);
    read_csv_token(&(entry->model), fp);
    read_csv_token(&(entry->color), fp);
    read_csv_token(&(entry->license_plate), fp);

    return entry;
}
node** read_csv_data(FILE *fp) {
    node **head=malloc(sizeof(node*));
    *head=create_node(read_csv_line(fp));

    fgetc(fp);    //tests the next bit to see if its the EOF
    while(!feof(fp)) {
        fseek(fp, -1, SEEK_CUR);

        vehicle *entry=read_csv_line(fp);
        node *n=create_node(entry);
        add_node(head, n);

        fgetc(fp);    //tests the next bit to see if its the EOF
    }

    return head;
}

int strcmp_insensitive(char *str1, const char *str2) {
    if(strlen(str1)!=strlen(str2)) {  //if they are different sizes then they can't match.
        return -1;  // Non-0 implementation is different so -1 is the default non-equal value.
    }
    for(int i=0; i<strlen(str1); i++) {
        if(tolower(str1[i])!=tolower(str2[i]))
            return -1;
    }
    return 0;
}
int contains_make(node **head, char *str) { //not case sensative.
    node *cur=*head;

    while(1) {
        if(!strcmp_insensitive(str, cur->data))
            return 1;

        if(cur->next==NULL)
            return 0;
        else
            cur=cur->next;
    }
}
node** generate_makes_list(node **head) {
    node **makes_list = malloc(sizeof(node*));
    *makes_list=create_node(((vehicle*)(*head)->data)->make);
    
    node *cur=*head;
    while(1) {
        char *buff=((vehicle*)cur->data)->make;   //the make of the car were determining whether has occured before.
        
        if(!contains_make(makes_list, buff)) {
            add_node(makes_list, create_node(buff));
        }
        if(cur->next==NULL)
            break;
        else
            cur=cur->next;
    }

    return makes_list;
}

char* make_input(node **makes_list) {
    char buff[STR_BUFF];
    printf("Select Make (#): ");
    fgets(buff, STR_BUFF, stdin);

    int input=atoi(buff);
    return get_node(makes_list, input-1)->data;
}

node** generate_selection_list(node **head, char *str) {
    node **selection = malloc(sizeof(node*));
    *selection=NULL;

    node *cur=*head;
    while(1) {
        int cmp = !strcmp_insensitive(((vehicle*)(cur->data))->make, str);
        if(cmp) {
            if(*selection==NULL)
                *selection=create_node(cur->data);
            else
                add_node(selection, create_node(cur->data));
        }

        if(cur->next==NULL)
            break;
        else
            cur=cur->next;
    }

    return selection;
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
    char file_type[STR_BUFF];
    strcpy(file_type, strchr(argv[1], '.'));
    if(strcmp(file_type, ".csv")) {  //determines whether the file type is correct.
        printf("Invalid file type. Exiting program.");
        return 0;
    }

    

    node **head = read_csv_data(fp);    //reads the csv data into the linked list **head.
    node **makes_list = generate_makes_list(head);  //generates a linked list of the different makes of cars.
    
    print_makes(makes_list);
    char* input = make_input(makes_list);

    node **selection = generate_selection_list(head, input);
    print_entries(selection);


    free_list(head, 0);    //frees all data from the 3 generated linked lists.
    free_list(makes_list, 1); //since makes_list holds char* as data, freeing data is different.
    free_list(selection, 0);
}
