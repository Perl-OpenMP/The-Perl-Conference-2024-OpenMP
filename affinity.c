#include <stdio.h>
#include <omp.h>

int main() {
    // Start a parallel region
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d is running on CPU %d\n", thread_id, sched_getcpu());
    }

    return 0;
}

