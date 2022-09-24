//Name: Landon Moon
//ID: 1001906270
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#define SIZE 4

int go_to_market(int chicken_eggs[]) { //determines whether there is enough eggs.
    int total = 0;

    for(int i=0; i<SIZE; i++) {
        total+=chicken_eggs[i];
    }
    
    if(total>=30)
        return 0;
    else
        return 1;
}
int value_found(char name[], char names[SIZE][20]) { //returns 1 if found. 0 if not.
    for(int i; i<SIZE; i++) {
        if(strcmp(name, names[i])==0)
            return 1;
    }
    return 0;
}
void give_chicken_info(int chicken_eggs[], char chicken_names[SIZE][20]) { //gets the names and values and puts them into chicken_eggs and chicken_names.
    for(int i=0;i<SIZE; i++) { //clears the names. chicken_eggs doesnt need to be cleared since the new number write over the old.
        strcpy(chicken_names[i],"");
    }

    for(int i=0; i<SIZE;i++) { //get names.
        printf("\n%d. Enter chicken name: ",i+1);
        while(1) { //while true loop. only exits if there is a break.
            char cur_name[20];
            scanf("%s", cur_name);

            if(!value_found(cur_name, chicken_names)) { //if there isn't that name already
                strcpy(chicken_names[i],cur_name);
                break;
            }
            else { //if the name is already used.
                printf("We already have a chicken named %s. Give another name: ", cur_name);
            }
        }

        printf("How many eggs did %s lay? ",chicken_names[i]); //gets the number of eggs laid. had some weird i/o issues but this works. scanf("%d") was locking the program for some reason.
        char num[10];
        scanf("%s", num);
        chicken_eggs[i]=atoi(num);
    }
}

int	main(int argc, char **argv) {
	int chicken_eggs[SIZE]={0};	/*size is defined by a preprocessor directive*/
	char chicken_names[SIZE][20];
	int	value=1;

	while(value) {
		printf("~~~Welcome to the best chicken farm ever!!!~~~\n");
		give_chicken_info(chicken_eggs,chicken_names);
		value=go_to_market(chicken_eggs);
		if(!value)
		{
			printf("Congrats Farmer Bob! You get to go sell your golden eggs at the market! Good bye and good luck! :)\n\n");
		}
		else
		{
	    	printf("Sorry Farmer Bob.  Let's try again to get enough golden eggs next month...\n\n");
		}
	}
}