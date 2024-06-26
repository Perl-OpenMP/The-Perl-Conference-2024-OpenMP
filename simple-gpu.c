#include <stdio.h>
#include <omp.h>

int main() {
    int a = 10, b = 20, c;

    #pragma omp target map(from:c)
    {
        c = a + b;
    }

    printf("Result: %d\n", c);

    return 0;
}
