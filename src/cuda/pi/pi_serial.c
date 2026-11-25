#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    int N = 1000000000;
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double x = (i + 0.5) / (double)N;
        sum += 4.0 / (1.0 + x*x);
    }

    double pi = sum / N;

    printf("Pi         = %.15f\n", pi);
    return 0;
}
