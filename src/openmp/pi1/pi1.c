#include <stdio.h>
#include <omp.h>
#define N 100000
int main(void) {
    double sum = 0.0;
    double dx = 1.0 / N;
    #pragma omp parallel
    {
    #pragma omp for
    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) * dx;
        sum += 4.0 / (1.0 + x*x);
    }
    }
    double pi = sum * dx;
   printf("Pi = %.15f\n", pi);
   return 0;
}
