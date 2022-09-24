#include <stdio.h>
#include <string.h> 

int main(int argc, char **argv) {
    printf("Please enter a number between 4-6: ");
    int num;
    scanf("%d",&num);

    if(!(num >= 4 && num <=6)) {
        printf("Number out of range!");
        return 0;
    }
    

    printf("Enter a word with at least %d letters and at most 10 letters: ", num);
    char word[20];
    scanf("%s", word);

    if(strlen(word)>10) {
        printf("Too many letters");
        return 0;
    }
    if(strlen(word)<num) {
        printf("Too many letters");
        return 0;
    }

    printf("Please enter another numberbetween 1-3: ");
    int num2; //pdf doesn't say anything about input verification for this part
    scanf("%d",&num2);

    char newWord[10];
    strncpy(newWord, word, num2);
    printf("%s",newWord);
}