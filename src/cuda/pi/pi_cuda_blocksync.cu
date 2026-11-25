#include <stdio.h>
#include <cuda_runtime.h>

#define THREADS_PER_BLOCK 256

__global__ void calc_pi(double *partial_sums, int N)
{
    // Shared memory: one value per thread
    __shared__ double sdata[THREADS_PER_BLOCK];

    int t = threadIdx.x;

    // Global thread index
    int tid = blockIdx.x * blockDim.x + threadIdx.x;

    // Total number of threads
    int stride = blockDim.x * gridDim.x;

    // -----------------------------------
    // 1. Grid-stride integration
    // -----------------------------------

    double local_sum = 0.0;

    for (int i = tid; i < N; i += stride) {

        double x = (i + 0.5) / (double)N;

        local_sum += 4.0 / (1.0 + x*x);
    }

    // -----------------------------------
    // 2. Store results in shared memory
    // -----------------------------------

    sdata[t] = local_sum;

    __syncthreads();

    // -----------------------------------
    // 3. Parallel reduction
    // -----------------------------------

    for (int offset = blockDim.x / 2;
         offset > 0;
         offset /= 2)
    {
        if (t < offset) {
            sdata[t] += sdata[t + offset];
        }

        __syncthreads();
    }

    // -----------------------------------
    // 4. Write one result per block
    // -----------------------------------

    if (t == 0) {
        partial_sums[blockIdx.x] = sdata[0];
    }
}


int main()
{
    int N = 1000000000;

    int threadsPerBlock = THREADS_PER_BLOCK;
    int blocks = 32;

    // -----------------------------------
    // Allocate partial sums on GPU
    // -----------------------------------

    double *d_partial;

    cudaMalloc(&d_partial, blocks * sizeof(double));

    // -----------------------------------
    // Launch kernel
    // -----------------------------------

    calc_pi<<<blocks, threadsPerBlock>>>(d_partial, N);

    // -----------------------------------
    // Copy partial sums to CPU
    // -----------------------------------

    double *h_partial = new double[blocks];

    cudaMemcpy(h_partial, d_partial,
               blocks * sizeof(double),
               cudaMemcpyDeviceToHost);

    // -----------------------------------
    // Final reduction on CPU
    // -----------------------------------

    double sum = 0.0;

    for (int i = 0; i < blocks; i++) {
        sum += h_partial[i];
    }

    double pi = sum / N;

    printf("Pi = %.15f\n", pi);

    // -----------------------------------
    // Cleanup
    // -----------------------------------

    delete[] h_partial;

    cudaFree(d_partial);

    return 0;
}

