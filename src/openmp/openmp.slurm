#!/bin/bash
#SBATCH --job-name=openmp
#SBATCH --partition=ffa
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --hint=nomultithread
#SBATCH --time=00:05:00
#SBATCH --output=openmp-%j.out

# gcc -O3 -march=native -fopenmp hello_omp.c -o hello_omp

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
export OMP_PLACES=cores
export OMP_PROC_BIND=close

srun ./hello_omp
