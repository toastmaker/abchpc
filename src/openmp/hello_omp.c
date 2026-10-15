#include <stdio.h>
#include <omp.h>

int main(void)
{
    int counter = 0;
    const int N = 1000000;

    // 1. Parallel region: each thread prints a greeting
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        printf("Hello from thread %d of %d\n", tid, nthreads);
    }

    // 2. Parallel for loop with an atomic counter
    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    {
//        #pragma omp atomic
        counter++;
    }

    printf("\nCounter:  %d\n", counter);
    printf("Expected: %d\n", N);

    return 0;
}
