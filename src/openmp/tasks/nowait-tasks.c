#include <stdio.h>
#include <omp.h>

int main(){

#pragma omp parallel
 {
  #pragma omp single nowait
   {
     printf("Hi, I’m thread %d and I am single and creating tasks\n", omp_get_thread_num());

     #pragma omp task
       {
         printf("Hi, I’m thread %d, running task A\n", omp_get_thread_num());
       } 
     #pragma omp task
       {
         printf("Hi, I’m thread %d, running task B\n", omp_get_thread_num());
       }
// }
     printf("Hi, I am thread %d at the end of the single region. Waiting for others\n", omp_get_thread_num());
}
}
return 0;
}
