#include <stdio.h>
#include <omp.h>

#define N 100
#define M 50

int main() {
    int matrix[N][M];
    int result[N][M];
    int i, j, k; // Declare loop indices outside of the loops

    // Initialize matrix
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            matrix[i][j] = i * M + j;
        }
    }

    // Parallel region with nested loop vectorization
    #pragma omp parallel for collapse(2) private(i, j, k)
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            #pragma omp simd
            for (k = 0; k < 4; ++k) { // Assume vector length is 4 (adjust as per architecture)
                result[i][j] += matrix[i][j] * k;
            }
        }
    }

    // Print result matrix
    printf("Result Matrix:\n");
    for (i = 0; i < N; ++i) {
        for (j = 0; j < M; ++j) {
            printf("%4d ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

