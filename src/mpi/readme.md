
salloc -p ffa --nodes=2 --ntasks-per-node=2 --time=00:10:00
srun python hellompi.py

mpirun -np 4 python hellompi.py

mpirun -np 4 --bind-to none hostname

mpirun -np 4 --map-by ppr:2:node --bind-to core --report-bindings python hellompi.py

# ppr means processes per resource (node|core|package)
# package is like a socket)
