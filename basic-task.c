#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        #pragma omp single     // Ensure only one thread creates the initial task
        {
          #pragma omp task
          {printf("Perl ");}   // Task #1 
          #pragma omp task
          {printf("rocks! ");} // Task #2
        }
    }
    return 0;
}
