#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "problem1.h"

#define BUFF 128

void a() {  //int
    int *num = malloc(sizeof(int));
    *num=1;

    //printf("DEBUG:%d", *num); //debug code

    free(num);
}
void b() {  //int[]
    char buff[BUFF];
    printf("Enter the size of the array (N): ");
    fgets(buff, BUFF, stdin);
    int N=atoi(buff);

    int *arr = malloc(N*sizeof(int));
    for(int i=0; i<N; i++) {
        arr[i]=1;
    }

    //printf("DEBUG:%d", arr[4]); //debug code

    free(arr);
}
void c() {  //int[][]
    char buff[BUFF];
    printf("Enter the size of the array (M N): ");
    fgets(buff, BUFF, stdin);
    int M=atoi(strtok(buff," \n"));
    int N=atoi(strtok(NULL," \n"));

    //printf("DEBUG:%d %d", M, N);    //debug code

    int **arr=NULL;
    arr=malloc(M*sizeof(int*));

    for(int i=0; i<M; i++) {
        arr[i]=malloc(N*sizeof(int));
        for(int j=0; j<N; j++) {
            arr[i][j]=1;
        }
    }

    //for(int i=0; i<M; i++) {  //debug code
    //    for(int j=0; j<N; j++) {
    //        printf("%d ", arr[i][j]);
    //    }
    //    printf("\n");
    //}

    for(int i=0; i<M; i++) {
        free(arr[i]);
    }
    free(arr);
}
void d() {  //int[][][]
   char buff[BUFF];
    printf("Enter the size of the array (B M N): ");
    fgets(buff, BUFF, stdin);
    int B=atoi(strtok(buff," \n"));
    int M=atoi(strtok(NULL," \n"));
    int N=atoi(strtok(NULL," \n"));

    int ***arr=NULL;
    arr=malloc(B*sizeof(int*));

    for(int i=0; i<B; i++) {
        arr[i]=malloc(M*sizeof(int));
        for(int j=0; j<M; j++) {
            arr[i][j]=malloc(N*sizeof(int));
            for(int k=0; k<N; k++) {
                arr[i][j][k]=1;
            }
        }
    } 

    for(int i=0; i<B; i++) {    //freeing data.
        for(int j=0; j<M; j++) {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
}
void e() {  //double
    double *num = malloc(sizeof(double));
    *num=1.61;

    free(num);
}
void f() {  //double[]
    char buff[BUFF];
    printf("Enter the size of the array (N): ");
    fgets(buff, BUFF, stdin);
    int N=atoi(buff);

    double *arr = malloc(N*sizeof(double));
    for(int i=0; i<N; i++) {
        arr[i]=1.0;
    }

    free(arr);
}
void g() {  //double[][]
    char buff[BUFF];    //getting user input
    printf("Enter the size of the array (M N): ");
    fgets(buff, BUFF, stdin);
    int M=atoi(strtok(buff," \n"));
    int N=atoi(strtok(NULL," \n"));

    double **arr=NULL;  //declaring array

    arr=malloc(M*sizeof(double*));  //allocating memory and initilizing values.
    for(int i=0; i<M; i++) {    
        arr[i]=malloc(N*sizeof(double));
        for(int j=0; j<N; j++) {
            arr[i][j]=1.0;
        }
    }

    for(int i=0; i<M; i++) {    //freeing memory.
        free(arr[i]);
    }
    free(arr);
}
void h() {  //char
    char *c = malloc(sizeof(char));
    *c='1';

    free(c);
}
void i() {  //char[]
    char buff[BUFF];
    printf("Enter the size of the array (N): ");
    fgets(buff, BUFF, stdin);
    int N=atoi(buff);

    char *arr = malloc(N*sizeof(char));
    for(int i=0; i<N; i++) {
        arr[i]=1;   //in the pdf you say "init vals to 1" instead of '1'
    }

    free(arr);
}
void j() {  //char[][]
    char buff[BUFF];
    printf("Enter the size of the array (M N): ");
    fgets(buff, BUFF, stdin);
    int M=atoi(strtok(buff," \n"));
    int N=atoi(strtok(NULL," \n"));

    //printf("DEBUG:%d %d", M, N);    //debug code

    char **arr=NULL;
    arr=malloc(M*sizeof(int*));

    for(int i=0; i<M; i++) {
        arr[i]=malloc(N*sizeof(int));
        for(int j=0; j<N; j++) {
            arr[i][j]=1;
        }
    }

    for(int i=0; i<M; i++) {    //freeing data
        free(arr[i]);
    }
    free(arr);
}

int main() {
    a();
    b();
    c();
    d();
    e();
    f();
    g();
    h();
    i();
    j();

    return 1;
}
