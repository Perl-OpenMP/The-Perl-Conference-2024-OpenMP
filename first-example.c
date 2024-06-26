#include <stdio.h>
#include <omp.h>

int main() {
  int ret = 0;
  #pragma omp parallel
  {
    #pragma omp single
    {
      ret = omp_get_num_threads();
    }
  }
  printf("running with %d threads\n", ret);
  return ret;
}
