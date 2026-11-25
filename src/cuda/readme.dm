# GPU notes

## SLURM

On SLURM to request GPU use `--gpus=1`, or `--gres='gpu:1'`` on gpu-xxx partitions

```$> alloc -p gpu-ffa --gres "mps:5" --mem 10G -t 12:0:0 --cpus-per-task 4```

`--gres 'gpu:1'` if you want entire GPU

```$> module load cuda/cuda-13.0```

## nvidia-hpc-sdk

```
$> module load nvidia-hpc-sdk
$> module load nvhpc/25.9
$> nvc -acc hello_acc.c -o hello_acc
```

`-gpu=ccnative`

```
nvc -O3 -acc -Minfo=accel|all|loop|par|inline|vect pi_acc.c -o pi_acc
```

## openMP

```
nvc -O3 -mp=gpu pi.c -o pi
```


## CUDA

```
$> module load cuda/13.0
$> nvcc -O3 pi.cu -o pi

salloc -p gpu-ffa --gres=gpu:1 --time=00:30:00
srun ./pi
```

```bash
#!/bin/bash
#SBATCH --job-name=cuda-pi
#SBATCH --partition=gpu-ffa
#SBATCH --gres=gpu:1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:10:00
#SBATCH --output=cuda-%j.out

module load cuda/13.0

srun ./pi
```

and submit it by `sbatch cuda.sbatch`


-arch=native
| Code          | Compiler | Command | 
| :----         | :---     | :----   |
| CUDA C/C++      | nvcc     | nvcc -O3 -arch=sm_89 pi.cu -o pi |
| CUDA C++        | nvc++    | nvc++ -O3 -cuda -gpu=cc89 pi.cu -o pi |
| OpenACC C       | nvc      | nvc -O3 -acc -gpu=cc89 pi.c -o pi |
| OpenMP target C | nvc      | nvc -O3 -mp=gpu -gpu=cc89 pi.c -o pi |

## Python Cupy

```
$> source ~/cupy-env/bin/activate
$> module load cuda/13.0
$> pip install cupy-cuda13
```
