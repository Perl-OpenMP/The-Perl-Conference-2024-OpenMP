#include <stdio.h>
#include <omp.h>

int fibonacci(int n) {
    if (n <= 2)
        return 1;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

int fibonacci_parallel(int n) {
    if (n <= 2)
        return 1;
    else {
        int fib1, fib2;
        
        #pragma omp task shared(fib1) // Create a task for calculating fibonacci(n-1)
        fib1 = fibonacci_parallel(n - 1);
        
        #pragma omp task shared(fib2) // Create another task for calculating fibonacci(n-2)
        fib2 = fibonacci_parallel(n - 2);
        
        #pragma omp taskwait // Wait for both tasks to complete
        
        return fib1 + fib2; // Combine results
    }
}

int main() {
    int n = 10;
    int result;

    #pragma omp parallel
    {
        #pragma omp single // Ensure only one thread creates the initial task
        result = fibonacci_parallel(n);
    }

    printf("Fibonacci(%d) = %d\n", n, result);

    return 0;
}

