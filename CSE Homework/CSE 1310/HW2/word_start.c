#include <stdio.h>
#include <string.h>
#include <ctype.h> 

int main(int argc, char **argv) {
    char word[20];
    printf("Please enter a word: ");
    scanf("%s", word);
    
    //I really want this to be in java and just do Character.isvowel(). I'm trying to look for an easier way than a bunch of if statements.
    //...ahhhh so theres a header to get isalpha. That helps a bit.
    
    char fl = tolower(word[0]); //if its a letter make it lowercase
    if(!isalpha(fl)) {  //if its not a letter
        printf("%s starts with neither a vowel nor a consonant.", word);
    } else if(fl=='a'|| //if its a vowel
              fl=='e'||
              fl=='i'||
              fl=='o'||
              fl=='u'||
              fl=='y') {
        printf("%s starts with a vowel.", word);
    } else { //if its a consonant
        printf("%s starts with a consonant.", word);
    }
}