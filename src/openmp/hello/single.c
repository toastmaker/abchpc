#include <stdio.h>
#include <omp.h>

int main(){

#pragma omp parallel
   {
   #pragma omp single
     {
     int nt = omp_get_num_threads();
     printf("nt = %d\n", nt);
     }
   }
return 0;
}

