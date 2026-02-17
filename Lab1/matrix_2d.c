#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000

int main() {
    static double A[N][N], B[N][N], C[N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = 1.0;
            B[i][j] = 1.0;
            C[i][j] = 0.0;
        }

    double start = omp_get_wtime();

    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    double end = omp_get_wtime();
    printf("2D Parallel Matrix Multiply Time: %f seconds\n", end - start);

    return 0;
}
