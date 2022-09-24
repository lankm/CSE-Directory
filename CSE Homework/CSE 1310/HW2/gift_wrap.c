#include <stdio.h>
#include <string.h> 

int main(int argc, char **argv) {
    printf("***Hello!  Please pick from the following options:***\n");
    printf("1) Buy standard wrapping paper-press 1\n");
    printf("2) Buy holiday edition wrapping paper-press 2\n");
    int choice;
    scanf("%d", &choice);

    if(choice==1) {
        printf("You have selected standard wrapping paper.\n");
    } else if(choice==2) {
        printf("You have selected holidaywrapping paper.\n");
    } else { //this would usually exit or loop around but the homework didn't say anything about it so I had some fun with the error message.
        printf("Thats not an option but the homework didn't say to exit. So you're wrapping paper will cost $%d per square inch\n",choice);
    }


    int length;
    int height;
    int width;
    printf("Please enter the size of your gift (in inches):\nLength: ");
    scanf("%d", &length);

    printf("Height: ");
    scanf("%d", &height);

    printf("Width: ");
    scanf("%d", &width);

    int surfaceArea = 2*(length*width+length*height+height*width);
    int cost = choice*surfaceArea;
    printf("You will pay $%d at the counter. Thank you for shopping with us!", cost);
}