#include <stdio.h>
#include <omp.h>

int main(void)
{
    const long long N = 100000000;
    double sum = 0.0;
    double start = omp_get_wtime();

    #pragma omp target teams distribute parallel for reduction(+:sum)
    for (long long i = 0; i < N; i++) {
        double x = (i + 0.5) / (double)N;
        sum += 4.0 / (1.0 + x*x);
    }

    double pi = sum / N;
    double end = omp_get_wtime();

    printf("Pi = %.15f\n", pi);
    printf("Time = %.6f s\n", end-start);
    return 0;
}
