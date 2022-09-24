//Student Name: Landon Moon
//Student ID: 1001906270
//P.S. I get sarcastic with my code so I hope you like some of the comments.
#include <stdio.h>
#include <ctype.h>
#include <string.h>
void tolowercase(char word[]); //prototype. I'm trying to do functions cause I have to make something lowercase twice. Its different from java.

int main(int argc, char **argv) {
    int patNum = 3;
    char patients[patNum][20];
    int pills[patNum];
    for(int i=0;i<patNum;i++) {//set all pill values to 0 to start.
        pills[i]=0; 
    }

    for(int i=0;i<patNum;i++) {//get the patient names in lowercase. If your name is exit sorry youre getting no pills.
        printf("Enter patient %d name: ", i+1);
        scanf("%s", patients[i]);
        tolowercase(patients[i]); //to make it not case sensative.
    }
    printf("\n");

    while(1) {//give patients pills
        char curName[20];
        printf("Enter patient name taking pills: ");
        scanf("%s", curName);
        tolowercase(curName);   //might at well make it not case sensative. :/

        if(strcmp(curName,"exit")==0) {//exit function
            printf("Exiting...\n\n");
            printf("Would you like to see the total pill amounts for each patient? ");

            while(1) {//loops until the user puts yes or no.
                char yn[10];
                scanf("%s", yn);
                tolowercase(yn);

                if(strcmp(yn,"yes")==0) {
                    for(int i=0;i<patNum;i++) {
                        patients[i][0] = tolower(patients[i][0]);
                        printf("%s: %d\n", patients[i], pills[i]);
                    }
                    return 1;//exit program.
                }
                else if(strcmp(yn,"no")==0) {
                    int totalPill=0;
                    for(int i=0;i<patNum;i++) {
                        totalPill+=pills[i];
                    }
                    printf("Ok. Total pills dispensed: %d",totalPill);
                    return 1; //exit program
                }
                else {
                    printf("Answer not recongnized. yes or no.");
                }
            }
        }

        int i=0;
        for(;i<patNum;i++) {//seatch for name. i stays around as the found index.
            if(strcmp(curName,patients[i])==0) {
                printf("Patient found-patient #%d! How many pills? ",i+1);
                break;
            }
        } 
        if(i==patNum) { //didnt find the name
            printf("Sorry, patient not found.\n\n");
            continue; //I know this from java and I hope it means the same thing... well it works so im going with it.
        }

        int curPills;
        scanf("%d",&curPills);
        pills[i]+=curPills;
        curName[0] = toupper(curName[0]);//uppercase first letter for name.
        printf("Total pills so far for %s: %d\n\n",curName,pills[i]);

    }
}
void tolowercase(char word[]) { //gonna figure out how to return an array later since its not important at the moment.
    for(int i = 0; word[i]; i++){
        word[i] = tolower(word[i]);
    }
}