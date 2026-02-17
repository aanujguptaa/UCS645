#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N (1 << 16)

int main() {
    double *X, *Y, a = 2.5;
    X = (double *)malloc(N * sizeof(double));
    Y = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        X[i] = i * 1.0;
        Y[i] = i * 2.0;
    }

    printf("Threads\tTime (seconds)\n");

    for (int threads = 2; threads <= 16; threads *= 2) {
        omp_set_num_threads(threads);

        double start = omp_get_wtime();

        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            X[i] = a * X[i] + Y[i];
        }

        double end = omp_get_wtime();
        printf("%d\t%f\n", threads, end - start);
    }

    free(X);
    free(Y);
    return 0;
}
