#include <stdio.h> 
#include <string.h>

#define HASHTABLESIZE 10 
int MyHashFunction(char *name) 
{ 
    /* the field system-name is used for the hash */
    int value=0;
    int len=strlen(name);
    for(int i=0;i<len;i++)
        value+=name[i];

    return value % HASHTABLESIZE; 
} 

int main() 
{ 
    char HashValue[20];
    printf("Enter value ");
    scanf("%s", HashValue);
    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue)); 
    return 0; 
}