//Name: Landon Moon
//ID: 1001906270
#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

int	valid_num(char credit_card[]) {
	return (strlen(credit_card)==16) && (credit_card[0]=='5'|| credit_card[0]=='4');
}
void get_creditcard_info(char wallet[][20],int cvv_numbers[], int cards) {
    for(int i=0;i<cards;i++) {
        printf("\n--%d. Enter credit card number: ",i+1);
        while(1) {
            char credit_card[20];
            scanf("%s",credit_card);

            if(valid_num(credit_card)) {
                strcpy(wallet[i],credit_card); //copies credit card number into list if valid.
                printf("Enter the CVV number: ");

                char cvv[3];
                scanf("%s",cvv);

                cvv_numbers[i]=atoi(cvv);
                break;
            }
            else {
                printf("Not a valid number. Enter a valid credit card number: ");
            }
        }
    }
}
int use_creditcard(char wallet[][20],int cvv_numbers[], int cards) {
    printf("\n--All credit cards in your wallet:\n"); //displays numbers
    for(int i=0; i<cards; i++) {
        printf("%d. %s\n", i+1, wallet[i]);
    }

    char card[20];
    int cvv;
    printf("\nEnter card to use: ");
    scanf("%s",card);
    printf("Enter CVV number: ");
    char cvv_char[5];
    scanf("%s",cvv_char); //%d doesn't work for some reason. it locks up the program. will figure out later.
    cvv=atoi(cvv_char);

    for(int i=0; i<cards; i++) {
        if(strcmp(wallet[i],card)==0 && cvv_numbers[i]==cvv) {
            return 1; //if card number and cvv match.
        }
    }
    return 0; //if the card doen't match any.
}

int	main(int argc, char **argv) {
	char wallet[3][20];
	int cvv_numbers[3];
	get_creditcard_info(wallet,cvv_numbers,3);
	int	answer=use_creditcard(wallet,cvv_numbers,3);
	if(answer) {
		printf("Card accepted! \n");
	}
	else {
		printf("Card rejected. \n");
	}
}