#include <stdio.h>
#include <omp.h>

int main() {
    int sum = 0;
    int i;
    // Parallel loop where each thread updates sum atomically
    #pragma omp parallel for shared(sum) private(i) // Specify sum as shared and i as private
    for (i = 0; i < 1000; ++i) {
        #pragma omp atomic
        sum += i;
    }
    printf("Sum: %d\n", sum);
    return 0;
}

