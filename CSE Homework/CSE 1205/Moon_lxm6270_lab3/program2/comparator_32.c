#include <stdio.h>

int main() {
	int a=0;
	int b=6;
	
	
	printf("a        a==b     a<b      a>b\n");
	for(int i=0; i<32;i++) {
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
			
		a=(a+1)%16;
	}
}

