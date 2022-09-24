#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 32

int main() {
	int A, B;
	char buffer[BUFF_SIZE];
	
	printf("Enter an integer for A: ");
	fgets(buffer, BUFF_SIZE,stdin);
	A=atoi(buffer);
   
	printf("Enter an integer for A: ");
	fgets(buffer, BUFF_SIZE,stdin);
	B=atoi(buffer);
	
	int and=0, or=0, not=0;
	
	if(A&&B)
		and=1;
	if(A||B)
		or=1;
	if(!(A||B))
		not=1;
		
	printf("A&&B: %d\n",and);
	printf("A||B: %d\n",or);
	printf("!(A||B): %d\n",not);
	
	return 0;
}

