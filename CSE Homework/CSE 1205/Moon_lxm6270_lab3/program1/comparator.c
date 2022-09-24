#include <stdio.h>

int main() {
	int b=6;
	
	
	printf("a        a==b     a<b      a>b\n");
	for(int a=0; a<512; a++) {
		printf("%-9d",a);
		
		if(a==b)
			printf("1        ");
		else
			printf("0        ");
		if(a<b)
			printf("1        ");
		else
			printf("0        ");
		if(a>b)
			printf("1\n");
		else
			printf("0\n");
	}
}
