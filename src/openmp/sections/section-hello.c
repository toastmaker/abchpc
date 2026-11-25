#include <stdio.h>
#include <omp.h>

int main(void) {
    #pragma omp parallel sections num_threads(3)
    {
        #pragma omp section
        {
            printf("A: thread %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("B: thread %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("C: thread %d\n", omp_get_thread_num());
        }
    }
    return 0;
}
