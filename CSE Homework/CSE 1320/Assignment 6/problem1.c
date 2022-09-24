#include "problem1.h"

node* create_node(vehicle *data) {
    node *n = malloc(sizeof(node));
    n->data=data;
    n->next=NULL;

    return n;
}   
void offer(node **queue, node *n) {
    if(*queue==NULL)
        *queue=n;
    else {
        node *cur=*queue;
        while(cur->next!=NULL) {    //traversing to end of list. Ineffecient but im tired and don't want to restructure my queue implementation.
            cur=cur->next;
        }
        cur->next=n;
    }
}
node* poll(node **queue) {
    node *n=*queue;
    *queue = (*queue)->next;

    return n;
}

void showList(char str_arr[][BUFFSIZE], int size) {
    for(int i=0; i<size; i++) {
        printf("%d. %s", i+1, str_arr[i]);
    }
}
void printn(node *n) {
    vehicle *v=n->data;
    printf("%d %s %s (%s) LIC#%s\n", v->year, v->make, v->model, v->color, v->license_plate);
}
char* getinput(char *output) {
    printf("> ");
    fgets(output, BUFFSIZE, stdin);

    output[strlen(output)-1]=0;   //trim

    return output;
}

void addVehicle(node **queue) {
    vehicle *v=makeVehicle();
    char buff[BUFFSIZE];

    printf("Enter the year\n");
    v->year = atoi(getinput(buff));

    printf("Enter the make\n");
    strcpy(v->make, getinput(buff));

    printf("Enter the model\n");
    strcpy(v->model, getinput(buff));

    printf("Enter the color\n");
    strcpy(v->color, getinput(buff));

    printf("Enter the license plate\n");
    strcpy(v->license_plate, getinput(buff));
    printf("\n");

    node *n=create_node(v);
    offer(queue, n);

}
void viewNextVehicle(node **queue) {
    char options[][BUFFSIZE] = {"Start Repair\n","Go back\n"};
    
    if((*queue)==NULL) {
        printf("No more vehicles\n\n");
        return;
    }
    else {
        printf("Next up: ");
        printn(*queue);
        showList(options, 2);
    }
    

    char buff[BUFFSIZE];
    int input=atoi(getinput(buff));
        
    switch (input) {
        case 1: 
            printf("Returning vehicle...\n\n"); 
            poll(queue); 
            break;
        case 2: 
            printf("\n"); 
            break;

        default: error(); break;
    }
}
void viewCurrentQueue(node **queue) {

    if(*queue==NULL) {
        printf("No cars in queue.\n\n");
        return;
    }

    node *cur_node=*queue;
    for(int i=0; cur_node!=NULL; i++) {
        printf("%d. ", i+1);

        printn(cur_node);
        cur_node=cur_node->next;
    }
    printf("\n");
}
void quit() {
    printf("Exiting program...\n");
}
void error() {
    printf("Wrong input. Returning to home.\n\n");
}

vehicle* makeVehicle() {
    vehicle *v=malloc(sizeof(vehicle));
    v->make=malloc(BUFFSIZE);
    v->model=malloc(BUFFSIZE);
    v->color=malloc(BUFFSIZE);
    v->license_plate=malloc(BUFFSIZE);

    return v;
}
void freequeue(node **queue) {
    node *cur = *queue;
    while(cur!=NULL) {
        node *next=cur->next;

        vehicle *v=cur->data;
        free(v->make);
        free(v->model);
        free(v->color);
        free(v->license_plate);
        free(cur);

        cur=next;
    }
}

int main(int argc, const char **argv) {
    char commands[][BUFFSIZE] = {"Add Vehicle\n","View Next Vehicle\n","View Current Queue\n","Quit\n"};
    node **queue = malloc(sizeof(node*));
    *queue=NULL;
    

    int status = 1;
    while(status) {
        showList(commands, 4);
        char buff[BUFFSIZE];
        int input=atoi(getinput(buff));
        
        switch (input) {
        case 1: addVehicle(queue); break;
        case 2: viewNextVehicle(queue); break;
        case 3: viewCurrentQueue(queue); break;
        case 4: quit(); status = 0; break;

        default: error(); break;
        }
    }

    freequeue(queue);
    free(queue);
}
