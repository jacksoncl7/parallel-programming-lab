g++ naive_omp_default.c -fopenmp -o3 -lm -o build/naive_omp_default
g++ naive_omp_atomic.c -fopenmp -o3 -lm -o build/naive_omp_atomic
g++ naive_omp_critical.c -fopenmp -o3 -lm -o build/naive_omp_critical