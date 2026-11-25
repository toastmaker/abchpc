#include <stdio.h>
#include <omp.h>

int main(void) {
    #pragma omp parallel num_threads(3)
    {
        #pragma omp single
        {
            for (int i = 0; i < 8; i++) {
                #pragma omp task firstprivate(i)
                {
                    printf("Task %d executed by thread %d\n", i, omp_get_thread_num());
                }
            }
            #pragma omp taskwait
            printf("All tasks finished\n");
        }
    }
    return 0;
}

