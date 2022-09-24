#include <stdio.h>

/*
 * Matrix multiplication on 3x3 matrices.
 * C is the zero matrix which will store the result of A * B.
 */
void matmul(float A[][3], float B[][3], float C[][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/*
 * Prints a 3x3 matrix.
 */
void print_matrix(float A[][3]) {
    for (int i = 0; i < 3; i++) {
        printf("|");
        for (int j = 0; j < 3; j++) {
            printf(" %5.0f", A[i][j]);
        }
        printf(" |\n");
    }
}

int main() {
    float A[3][3] = {{1, 5, -3},
                     {6, -9, 2},
                     {-2, 1, 7}};

    float B[3][3] = {{7, -6, 3},
                     {1, 9, -1},
                     {-8, 2, 2}};

    float C[3][3] = { 0 };

    matmul(A, B, C);

    print_matrix(C);

    fprintf(stderr, "ERROR: Nothing is really wrong.\n");

    return 0;
}
