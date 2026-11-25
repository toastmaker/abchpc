import numpy as np
import time
from numba import vectorize, float32, cuda
from numba import get_num_threads, config

@vectorize([float32(float32, float32, float32)], target='cuda')
def saxpy(a, x, y):
    return a*x + y

a = 3.141
x = np.random.rand(1024, 2048)
y = np.random.rand(1024, 2048)

# Warm-up: compile and initialize CUDA
result = saxpy(a, x, y)

cuda.synchronize()

N = 100

start = time.perf_counter()

for _ in range(N):
    result = saxpy(a, x, y)

cuda.synchronize()

elapsed = time.perf_counter() - start

print(f"Target: CUDA")
print(f"Average time: {elapsed/N*1000:.3f} ms")
print(result[0, 0])
