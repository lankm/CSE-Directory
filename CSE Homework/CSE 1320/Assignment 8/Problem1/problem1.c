#include "problem1.h"

void load_vehicles(FILE *fp, BTNode **root) {

    while(!feof(fp)) {
        char line[BUF_SIZE];
        fgets(line, BUF_SIZE, fp);

        char *token = strtok(line, ",");
        int num_tokens = 0;

        
        vehicle_t* v = malloc(sizeof(vehicle_t));

        while (token != NULL) {
            switch (num_tokens) {
                case 0:
                    v->year = atoi(token);
                    break;
                case 1:
                    v->make = calloc(strlen(token), sizeof(char));
                    strcpy(v->make, token);
                    break;
                case 2:
                    v->model = calloc(strlen(token), sizeof(char));
                    strcpy(v->model, token);
                    break;
                case 3:
                    v->color = calloc(strlen(token), sizeof(char));
                    strcpy(v->color, token);
                    break;
                case 4:
                    token[strlen(token)-1] = 0;

                    v->license_plate = calloc(strlen(token), sizeof(char));
                    strcpy(v->license_plate, token);
                    break;
            }

            num_tokens++;
            token = strtok(NULL, ",");
        }

        BTNode *temp = insert(root, v->year);
        temp->v=v;
    }
}

int main(int argc, const char **argv) {
    if (argc!=2) {  //program usage
        printf("USAGE: ./a.out FILENAME\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "rb");  //opens file and exits if not found.
    if(fp==NULL) {
        printf("\"%s\" could not be found. Exiting program.\n", argv[1]);
        return 1;
    }

    char file_type[BUF_SIZE];
    strcpy(file_type, strchr(argv[1], '.'));
    if(strcmp(file_type, ".csv")) {  //determines whether the file type is correct.
        printf("Invalid file type. Exiting program.\n");
        return 0;
    }

    
    BTNode **root = malloc(sizeof(BTNode*));
    *root=NULL;
    
    load_vehicles(fp, root);

    char commands[CMDS][BUF_SIZE] = {"Traverse Tree","Search","Exit"};
    int exit = 0;
    while(!exit) {
        for(int i=0; i<CMDS; i++) {
            printf("%d. %s\n", i+1, commands[i]);
        }
        printf("> ");

        char buffer[BUF_SIZE];
        fgets(buffer, BUF_SIZE, stdin);

        switch (atoi(buffer)) {
            case 1:
                dfs(*root, INORDER);
                break;
            case 2:
                printf("Enter year ");
                fgets(buffer, BUF_SIZE, stdin);
                BTNode *result = search(*root, atoi(buffer));
                if(result==NULL)
                    printf("Unable to find a vehicle made in the year %d.\n", atoi(buffer));
                else
                    print_vehicle(result->v);
                break;
            case 3:
                exit=1;
                break;
            default: 
                printf("Invalid input. Try again...\n");
                break;
        }
    }

    release_tree(*root);
}
