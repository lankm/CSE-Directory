//Name: Landon Moon
//ID: 1001906270
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char monthly_expenses[5][20]={"car payment","electricity","rent","groceries","going out"};
float expenses_money[5]={450.50,90.00,1800.00,400.00,500.00};
float monthly_payments_income[2][2]={{.60,.40},{4000.50,3000.25}};

char options[4][30]={"Continue (to the next month)","Make a life change?","Buy something using savings","Exit"};
char months[12][20]={"January","Feburary","March","April","May","June","July","August","September","October","November","December"};
int curmonth=0; //index of current month
int year;

float savings=0;


float print_out_monthly(char monthly_expenses[][20], float expenses_money[], float monthly_payments_inclome[][2]); //parameters are redundant but the assignment requires them
int life_change(char monthly_expenses[][20], float expenses_money[], float monthly_payments_inclome[][2]); //parameters are redundant but the assignment requires them
void change_split();
void change_income();
void next_choice(); 
void spend_money();
void next_month();
float total_expences(int j);

int main(int argc, char **argv) {
    printf("What year is it? ");
    scanf("%d",&year);

    while(1) {
        print_out_monthly(monthly_expenses, expenses_money, monthly_payments_income); //you probably are assuming the arrays are in main but keeping them out makes it easier. These parameter are redundant
        //also updating savings inside the method keeps everything cleaner and easier to understand. So uh I'm not gonna use the return value. It still returns the right value if that makes you happy.
        next_choice();
        next_month();
    }
}
float print_out_monthly(char monthly_expenses[][20], float expenses_money[], float monthly_payments_income[][2]) {
    float you=monthly_payments_income[1][0]; //get the monthly income
    float roommate=monthly_payments_income[1][1];

    printf("\n***Month: %s %d***\n",months[curmonth],year);
    for(int i=0; i<5;i++) { //displays expences
        float you_pay=expenses_money[i]*monthly_payments_income[0][0]; //calculate how much each pays
        float roommate_pay=expenses_money[i]*monthly_payments_income[0][1];

        you-=you_pay; //deducts the money from eaches income.
        roommate-=roommate_pay;

        printf("%s: $%.2f\n", monthly_expenses[i], expenses_money[i]);
        printf("---You pay: $%.2f  Roommate pays: $%.2f\n\n",you_pay,roommate_pay);
    }
    float total=you+roommate;
    printf("After all deductions:\n"); //displays totals
    printf("You have $%.2f left.  Roomate has $%.2f.  You have a total of $%.2f left after paying all bills.\n",you,roommate,total);

    char answer[20];
    printf("Would you like to put this in savings? ");
    scanf("%s",answer);

    if(!strcmp(answer,"yes")) { //only accepts "yes" anything else is no. I don't want to complicate this program and do input verification.
        savings+=total;
        printf("Ok. adding $%.2f to savings.  Total savings: $%.2f", total, savings);
    }
    else {
        printf("Ok.  Total savings so far: $%.2f", savings);
    }
    return total; //because im updating it within the method to keep things cleaner this is never used in main.
}
void next_choice() {
    printf("\n\nwould you like to:\n");
    for(int i=0; i<4;i++) {
        printf("%d. %s\n",i+1,options[i]);
    }
    int choice;
    scanf("%d",&choice);
    if(choice==1) {//if this was java I would use a switch statement but I don't think c has it

    } else if(choice==2) { //no if statement for 1 since it just goes to the next month
        life_change(monthly_expenses, expenses_money, monthly_payments_income); //parameters are redundant but the assignment requires them
    } else if(choice==3) {
        spend_money();
    } else if(choice==4) {
        printf("Bye!");
        exit(1);
    } //if you dont put a valid choice then it just goes to the next month
        
    printf("Ok. onwards to next month!");
}
int life_change(char monthly_expenses[][20], float expenses_money[], float monthly_payments_inclome[][2]) {
    int choice;
    printf("What life change are you making?  1. Change the split 2. Change income\n");
    scanf("%d",&choice);

    if(choice==1)
        change_split();
    else
        change_income();

    return 1; //all income problems are dealt with inside change_split and change_income so life change would always return 1. its not used anyway
}
void change_split() {
    //I should probably check to make sure the split wouldn't cuase me or the roommate to not be able to pay but the assignment doesn't say to in this method.
    float you_split;
    float roommate_split;

    printf("What is the new split?\n");
    printf("you: ");
    scanf("%f",&you_split);
    printf("roommate: ");
    scanf("%f",&roommate_split);

    if(you_split+roommate_split!=1){
        printf("That is not a valid split.\n\n");
        change_split(); //trying out recursion. I know it takes up more memory and a while loop would probably be better.
        return;
    }
    else {
        monthly_payments_income[0][0]=you_split;
        monthly_payments_income[0][1]=roommate_split;
    }
}
void change_income() {
    while(1) {
        char name[20];
        printf("Who is updating income?\n");
        scanf("%s",name); //ok so i'm learning that no one really uses scanf because its weird. i'll start using only fgets in my programs after this
        //if you put in two words at one it will say not a valid answer twice.

        if(!strcmp(name,"me")) {
            float income;
            printf("New amount? ");
            scanf("%f", &income);

            if(total_expences(0)>income) {
                char answer[20];
                printf("Are you sure about this update");
                scanf("%s", answer);

                if(!strcmp(answer,"yes")) {
                    printf("Alright. bye!");
                    exit(1);
                }
            }
            break;
        } else if(!strcmp(name,"roommate")) {
            float income;
            printf("New amount? ");
            scanf("%f", &income);

            if(total_expences(0)>income) {
                char answer[20];
                printf("Are you sure about this update");
                scanf("%s", answer);

                if(!strcmp(answer,"yes")) {
                    printf("Alright. bye!");
                    exit(1);
                }
            }
            break;
        } else {
            printf("not a valid answer.  ");
        }
    }
}
float total_expences(int j) { //j is whether its you or your roommate
    float total=0;

    for(int i=0; i<5;i++) { //displays expences
        total+=expenses_money[i]*monthly_payments_income[0][j]; //calculate how much each pays
    }
    return total;
}
void spend_money() {
    char item[20];
    printf("What are you buying? ");
    scanf("%s",item);

    char money[20];
    printf("How much is it? ");
    scanf("%s",money);
    if(money[0]=='$')
        memmove(money, money+1, strlen(money)); //removes $
    int worth=atoi(money);

    if(worth>savings)
        printf("Sorry. not enough savings for that.\n\n\n");
    else {
        savings-=worth;
        printf("Congratulations you now have a %s\n", item);
        printf("You now have %.2f in savings\n\n\n",savings);
    }
}
void next_month() {
    curmonth+=1;
    if(curmonth>=12) {
        year+=1;
        curmonth-=12;
    }
}