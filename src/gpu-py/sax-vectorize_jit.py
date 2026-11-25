import numpy as np
import time
from numba import njit

@njit(parallel=True)
def saxpy(a, x, y):
    return a*x + y

a = 3.141
x = np.random.rand(1024, 2048)
y = np.random.rand(1024, 2048)

result = saxpy(a, x, y)

N = 100

start = time.perf_counter()

for _ in range(N):
    result = saxpy(a, x, y)

elapsed = time.perf_counter() - start

print(f"Average time: {elapsed/N*1000:.3f} ms")
print(result[0, 0])
